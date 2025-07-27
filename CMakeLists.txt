cmake_minimum_required(VERSION 3.5)
project(tornado_catcher)

find_package(glfw3 REQUIRED)
find_package(SFML CONFIG COMPONENTS graphics system REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(screenmgr SHARED src/graphics/screenmanager.cpp)
add_library(fontutils SHARED src/graphics/font.cpp)
add_library(gl_utils SHARED src/graphics/mesh.cpp src/graphics/texture.cpp src/graphics/shader.cpp)
add_library(others SHARED src/other/time.cpp src/other/logger.cpp)
add_library(window SHARED src/window/window.cpp src/window/event.cpp)

target_link_libraries(window PUBLIC glfw PRIVATE OpenGL::GL GLEW screenmgr)
target_link_libraries(fontutils PRIVATE Freetype::Freetype)
target_link_libraries(gl_utils PRIVATE OpenGL::GL sfml-graphics)
target_link_libraries(screenmgr PRIVATE gl_utils)

add_executable(main src/main.cpp src/game.cpp )
target_link_libraries(main PRIVATE others fontutils window OpenGL::GL gl_utils sfml-graphics)