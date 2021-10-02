cmake_minimum_required(VERSION 3.14)
project(bingplugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)

add_library(bingplugin MODULE
    bingplugin.cpp bingplugin.h bingsettings.cpp bingsettings.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressable.h icons.qrc ../imagepluginerrorutil.h
)

set_target_properties(bingplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../plugins)

target_include_directories(bingplugin PUBLIC
    ../
    ../../
    ../../../model/pluginusage
    ../../../model
)


target_link_libraries(bingplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)




