file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${ENGINE_SOURCES})

target_include_directories(${EXECUTABLE_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
)

target_compile_options(${EXECUTABLE_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/permissive->)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    Game
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    OpenGL::GL
    OpenGL::GLU
)

# Copy the SDL runtime DLLs next to .exe so it can run without
# manually adjusting PATH.
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${EXECUTABLE_NAME}>
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
    COMMAND_EXPAND_LISTS
)

# The devel packages also bundle optional codec DLLs (webp/tiff/avif for
# SDL2_image, ogg/opus for SDL2_mixer, ...) under lib/x64/optional that
# aren't separate CMake targets, so TARGET_RUNTIME_DLLS above won't catch
# them. Copy everything from each package's lib/x64 tree as well.
foreach(dep_dir ${sdl2_SOURCE_DIR} ${sdl2-image_SOURCE_DIR} ${sdl2-mixer_SOURCE_DIR} ${sdl2-ttf_SOURCE_DIR})
    file(GLOB_RECURSE _dep_dlls "${dep_dir}/lib/x64/*.dll")
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_dep_dlls} $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
    )
endforeach()

# Copy the resources folder next to .exe so it can run without
# manually adjusting the working directory.
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/game/resources
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/resources
)
