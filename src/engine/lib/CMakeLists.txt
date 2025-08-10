cmake_minimum_required(VERSION 3.5)

find_package(glfw3 REQUIRED)
find_package(SFML CONFIG COMPONENTS graphics system REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(lite_window STATIC window/window.cpp window/event.cpp window/err_window.cpp)
add_library(lite_utils STATIC utils/logger.cpp utils/time.cpp)
add_library(lite_glutils STATIC glutils/mesh.cpp glutils/texture.cpp glutils/shader.cpp glutils/glctrl.cpp)
add_library(lite_buffer STATIC buffer/buffers.cpp)
add_library(gameldr STATIC gameldr/gameldr.cpp)
add_library(args STATIC args.cpp)

target_link_libraries(lite_window PUBLIC glfw PRIVATE OpenGL::GL GLEW::GLEW)
target_link_libraries(lite_glutils PRIVATE OpenGL::GL GLEW::GLEW sfml-graphics)
target_link_libraries(lite_utils PRIVATE args)
target_link_libraries(lite_buffer PRIVATE lite_utils)

add_library(lite3d SHARED lite3d.cpp)


target_link_libraries(lite3d PRIVATE lite_window lite_utils lite_buffer lite_glutils gameldr args sfml-graphics)
include_directories(${CMAKE_HOME_DIRECTORY}/src/engine/include/)
if(WIN32)
set_target_properties(lite3d PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
else()
set_target_properties(lite3d PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
endif()
set_target_properties(lite_window lite_utils lite_glutils gameldr args PROPERTIES POSITION_INDEPENDENT_CODE ON)