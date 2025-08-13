cmake_minimum_required(VERSION 4.0)
project(tornado_catcher)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED TRUE)

add_subdirectory("src/engine/lib")
add_subdirectory("src/tornado_chaser")

if(WIN32)
add_executable(main WIN32 src/engine/lib/main.cpp)
else()
add_executable(main src/engine/lib/main.cpp)
endif()
target_link_libraries(main PRIVATE lite3d lite_utils args lite_window)
target_include_directories(main PRIVATE ${CMAKE_HOME_DIRECTORY}/src/engine/include/)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
#set_target_properties(main PROPERTIES OUTPUT_NAME "tornado_chaser" DEBUG_POSTFIX "_DEBUG" RELEASE_POSTFIX "_RELEASE")