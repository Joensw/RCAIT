cmake_minimum_required(VERSION 3.14)

project(folderplugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)


add_library(folderplugin MODULE
  folderconfigwidget.h folderconfigwidget.cpp folderconfigwidget.ui folderplugin.cpp folderplugin.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressable.h icons.qrc
)

set_target_properties(folderplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../plugins)


target_include_directories(folderplugin PUBLIC
    ../
    ../../../model/pluginusage
)

target_link_libraries(folderplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)
