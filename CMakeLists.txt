cmake_minimum_required(VERSION 3.25)

project(YSNetwork
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# target 설정
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(ysNetwork ${sources})

if (WIN32)
    target_compile_definitions(ysNetwork PUBLIC WIN32)
elseif(UNIX)
    target_compile_definitions(ysNetwork PUBLIC UNIX)
endif()

install(DIRECTORY   ${CMAKE_SOURCE_DIR}/inc/
    DESTINATION     ${CMAKE_INSTALL_PREFIX}/inc/YSNetwork)
install(TARGETS     ysNetwork
    DESTINATION     ${CMAKE_INSTALL_PREFIX}/lib/YSNetwork)