cmake_minimum_required(VERSION 3.14)

project(mmclassificationplugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Svg)
find_package(Qt6 COMPONENTS SvgWidgets)

add_library(mmclassificationplugin MODULE
    mmclassificationplugin.cpp mmclassificationplugin.h mmclassificationsettings.cpp mmclassificationsettings.h mmclassificiationdataaugmentationinput.cpp mmclassificiationdataaugmentationinput.h mmclassificationinputoptions.cpp mmclassificationinputoptions.h basemodel.cpp basemodel.h model.cpp model.h mmclassificationconfigfilebuilder.cpp mmclassificationconfigfilebuilder.h mmclassificationjsonresultreader.cpp mmclassificationjsonresultreader.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressableplugin.cpp ../../../model/pluginusage/progressable.h ../../../model/pluginusage/progressable.cpp ../../results/trainingresult.h ../../results/trainingresult.cpp ../../results/classificationresult.h ../../results/classificationresult.cpp
)

set_target_properties(mmclassificationplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../plugins)

target_include_directories(mmclassificationplugin PUBLIC
    ../
    ../../results
    ../../../model/pluginusage
)

target_link_libraries(mmclassificationplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Svg
    Qt::SvgWidgets
)
