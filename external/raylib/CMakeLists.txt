include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
    GIT_SHALLOW TRUE
)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "Build raylib games" FORCE)
set(OPENGL_VERSION "4.3" CACHE STRING "OpenGL version to use" FORCE)

FETCHCONTENT_MAKEAVAILABLE(raylib)