cmake_minimum_required(VERSION 3.9.0)

set(CMAKE_BUILD_TYPE Debug)
find_package(glfw3 REQUIRED)
find_package(SFML CONFIG COMPONENTS network graphics system REQUIRED)

add_executable(listener listener.cpp)
add_library(tornado_chaser SHARED game.cpp)

target_link_libraries(tornado_chaser PRIVATE lite_utils lite_buffer lite_glutils glfw sfml-network lite_graphics lite3d) 
target_link_libraries(listener PRIVATE sfml-network)
target_include_directories(tornado_chaser PRIVATE ../src/engine/)

if(WIN32)
set_target_properties(tornado_chaser PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
else()
set_target_properties(tornado_chaser PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
endif()
include_directories(${CMAKE_HOME_DIRECTORY}/src/engine/include/)