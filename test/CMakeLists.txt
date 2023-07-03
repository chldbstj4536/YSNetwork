cmake_minimum_required(VERSION 3.25)

project(YSNetworkTest
    LANGUAGES CXX)

execute_process(COMMAND ${CMAKE_COMMAND} -S .. -B ../build -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} )
execute_process(COMMAND ${CMAKE_COMMAND} --build ../build --target install)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ysNetworkTest main.cpp)

target_include_directories(ysNetworkTest
    PUBLIC ${CMAKE_INSTALL_PREFIX}/inc)
target_link_libraries(ysNetworkTest
    PUBLIC ${CMAKE_INSTALL_PREFIX}/lib/YSNetwork/ysNetwork.lib)