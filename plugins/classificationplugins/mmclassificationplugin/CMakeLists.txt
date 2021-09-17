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
    mmclassificationplugin.cpp mmclassificationplugin.h mmclassificationsettings.cpp mmclassificationsettings.h mmclassificationdataaugmentationinput.cpp mmclassificationdataaugmentationinput.h mmclassificationinputoptions.cpp mmclassificationinputoptions.h basemodel.cpp basemodel.h model.cpp model.h mmclassificationconfigfilebuilder.cpp mmclassificationconfigfilebuilder.h mmclassificationjsonresultreader.cpp mmclassificationjsonresultreader.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressable.h ../../../model/results/genericresultgraphics.h ../../../model/results/genericresultgraphics.cpp ../../../model/results/classificationgraphics.h ../../../model/results/classificationgraphics.cpp  ../../../model/results/accuracycurve.h ../../../model/results/accuracycurve.cpp ../../../model/results/confusionmatrix.h ../../../model/results/confusionmatrix.cpp ../../results/result.h ../../results/result.cpp ../../results/trainingresult.h ../../results/trainingresult.cpp ../../results/classificationresult.h ../../results/classificationresult.cpp

    ../../../model/results/resultsprocessor.h ../../../model/results/resultsprocessor.cpp

    ../../../view/results/trainingresultview.h ../../../view/results/trainingresultview.cpp

        ../../../view/results/genericgraphicsview.h
        ../../../view/results/genericgraphicsview.cpp
        ../../../view/results/topaccuraciesview.h ../../../view/results/topaccuraciesview.cpp
        ../../../model/results/topaccuraciesgraphics.h ../../../model/results/topaccuraciesgraphics.cpp
        ../../../model/results/genericresultgraphics.h
        ../../../model/projectmanager.h
        ../../../model/projectmanager.cpp

    ../../../view/results/classificationresultview.h ../../../view/results/classificationresultview.cpp

        ../../../view/utilities/canvas.h ../../../view/utilities/canvas.cpp

        ../../../view/utilities/imagegallery.h ../../../view/utilities/imagegallery.cpp

        ../../../view/utilities/customtablewidget.h ../../../view/utilities/customtablewidget.cpp

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
