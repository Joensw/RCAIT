cmake_minimum_required(VERSION 3.14)
project(flickrplugin LANGUAGES CXX)

set(This FlickrPluginTests)

set(Sources
    testfile.cpp)


add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    flickrplugin
)


add_test(
    NAME ${This}
    COMMAND ${This}
)
