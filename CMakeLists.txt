cmake_minimum_required(VERSION 3.18) # file(ARCHIVE_EXTRACT ...) requires 3.18+

# Project name (root folder name by default):
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)

# Executable name (root folder name without lab number by default):
if(PROJECT_NAME MATCHES "^[^_]+_(.*)$")
    set(EXECUTABLE_NAME "${CMAKE_MATCH_1}")
else()
    set(EXECUTABLE_NAME "${PROJECT_NAME}")
endif()

project(${PROJECT_NAME} LANGUAGES CXX)

# Enforce C++17 for the entire project
set(CMAKE_CXX_STANDARD 17)              # Request C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Make C++17 Manditory instead of preferred
set(CMAKE_CXX_EXTENSIONS OFF)          # Don't allow compiler specific extensions (aka use the standard and nothing else)

# The SDL "devel VC" packages (headers + prebuilt .lib/.dll, no source) are
# cached on disk under C:/Prog1 instead of being fetched into the build tree
# on every configure. If a package isn't cached yet, it is downloaded and
# extracted into place once; subsequent configures (including from other
# build directories) just reuse the cached copy.
set(PROG1_LIBRARIES_DIR "C:/Prog1/Libraries" CACHE PATH "Root directory containing the SDL devel packages")

set(sdl2_SOURCE_DIR ${PROG1_LIBRARIES_DIR}/SDLMain/SDL2-2.26.3)
set(sdl2-image_SOURCE_DIR ${PROG1_LIBRARIES_DIR}/SDLImage/SDL2_image-2.6.3)
set(sdl2-mixer_SOURCE_DIR ${PROG1_LIBRARIES_DIR}/SDLMixer/SDL2_mixer-2.6.3)
set(sdl2-ttf_SOURCE_DIR ${PROG1_LIBRARIES_DIR}/SDLTtf/SDL2_ttf-2.20.2)

set(sdl2_url "https://github.com/libsdl-org/SDL/releases/download/release-2.26.3/SDL2-devel-2.26.3-VC.zip")
set(sdl2-image_url "https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip")
set(sdl2-mixer_url "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-devel-2.6.3-VC.zip")
set(sdl2-ttf_url "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-VC.zip")

# SHA256 of each zip, verified against the official GitHub release assets.
# Guards against a corrupted/truncated download silently poisoning the cache.
set(sdl2_sha256 "3b561bfcd7676d42f2b84ebde12d7433d176035ed28335c4fb9e554ef2764ec5")
set(sdl2-image_sha256 "5e54fa63d36358c2a310cc8ec1f5fda524c3011b1f7af1ebeadc58fef0c55ed9")
set(sdl2-mixer_sha256 "5d711b50e83a26e7a3cd221a0ba44828fdbe8d001869b64c3da6c8e73729bca4")
set(sdl2-ttf_sha256 "887b2b9d53c23f199c0d358a9d518d14f5cfd5245cde678747faa77535e60b5b")

foreach(dep sdl2 sdl2-image sdl2-mixer sdl2-ttf)
    
    # Set variable current_dependency_dir to the source directory of each SDL library 
    set(dep_dir ${${dep}_SOURCE_DIR})

    # Fetching logic, if path is not found:
    if(NOT EXISTS ${dep_dir})
        get_filename_component(_dep_parent ${dep_dir} DIRECTORY)
        
        # This is temporary
        set(_dep_zip_path "${_dep_parent}/${dep}.zip")

        message(STATUS "SDL package not cached at ${dep_dir} - downloading ${${dep}_url}")

        # Create the directory if it doesn't exist already
        file(MAKE_DIRECTORY ${_dep_parent})

        # Download the file in the temporary zip path

        file(DOWNLOAD ${${dep}_url} ${_dep_zip_path}
            STATUS _dep_dl_status
            SHOW_PROGRESS
            EXPECTED_HASH SHA256=${${dep}_sha256}
        )

        list(GET _dep_dl_status 0 _dep_dl_code)
        if(NOT _dep_dl_code EQUAL 0)
            list(GET _dep_dl_status 1 _dep_dl_error)
            file(REMOVE ${_dep_zip_path})
            message(FATAL_ERROR "Failed to download ${${dep}_url}: ${_dep_dl_error}")
        endif()

        # Extract the zip
        file(ARCHIVE_EXTRACT INPUT ${_dep_zip_path} DESTINATION ${_dep_parent})
        
        # Delete the zipped file
        file(REMOVE ${_dep_zip_path})

        if(NOT EXISTS ${dep_dir})
            message(FATAL_ERROR "Downloaded and extracted ${${dep}_url} but ${dep_dir} still doesn't exist - check the archive layout")
        endif()
    endif()
endforeach()

# Each devel package ships its own CMake package config, defining the same
# imported targets used below (SDL2::SDL2, SDL2_image::SDL2_image, ...).
list(APPEND CMAKE_PREFIX_PATH
    ${sdl2_SOURCE_DIR}/cmake
    ${sdl2-image_SOURCE_DIR}/cmake
    ${sdl2-mixer_SOURCE_DIR}/cmake
    ${sdl2-ttf_SOURCE_DIR}/cmake
)

# The bundled SDL package configs declare an old cmake_minimum_required()
# that recent CMake versions reject; raise the policy floor just for
# find_package() below instead of touching the vendored files.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
unset(CMAKE_POLICY_VERSION_MINIMUM)

find_package(OpenGL REQUIRED)

add_subdirectory(game)
add_subdirectory(engine)
