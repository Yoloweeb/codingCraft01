file(GLOB GAME_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(Game STATIC ${GAME_SOURCES})

target_precompile_headers(Game PRIVATE
    "${CMAKE_SOURCE_DIR}/engine/include/engine/pch.h"
)

target_include_directories(Game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include       
    PRIVATE ${CMAKE_SOURCE_DIR}/engine/include         
)

target_compile_options(Game PRIVATE /WX)
target_link_libraries(Game PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    OpenGL::GL
    OpenGL::GLU
)
