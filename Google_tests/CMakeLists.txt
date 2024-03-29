# 'Google_test' is the subproject name
cmake_minimum_required(VERSION 3.5)
project(Google_tests)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets LinguistTools Svg SvgWidgets Test)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets Qt6::Test)
set(CMAKE_AUTOUIC_SEARCH_PATHS  ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)


# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

#include directories so that the inclusion of header files works without specifying the path
set(MY_INCLUDE_DIRECTORIES ../plugins
    ../
    ../model
    ../model/results
    ../model/utilities
    ../model/pluginusage
    ../model/automation
    ../plugins/imageplugins
    ../plugins/classificationplugins
    ../plugins/results
    ../view
    ../view/results
    ../view/utilities
    ../controller)

# 'Google_Tests_run' is the target name

set(Sources
        #test_imageinspectionmodel.cpp
        ../model/imageinspectionmodel.h
        ../model/imageinspectionmodel.cpp

        test_automator.cpp
        ../model/automation/automator.h
        ../model/automation/automator.cpp

        test_task.cpp
        ../model/automation/task.h
        ../model/automation/task.cpp
        ../model/datamanager.h
        ../model/datamanager.cpp
        ../model/settingsmanager.h
        ../model/settingsmanager.cpp
        ../model/configurationmanager.h
        ../model/configurationmanager.cpp
        ../model/modelmanager.h
        ../model/modelmanager.cpp
        ../model/pluginusage/progressable.h
        ../model/pluginusage/imageloader.h
        ../model/pluginusage/imageloader.cpp
        ../model/pluginusage/classifier.h
        ../model/pluginusage/classifier.cpp
        ../model/pluginusage/trainer.h
        ../model/pluginusage/trainer.cpp
        ../model/automation/command.h
        ../model/automation/classificationcommand.h
        ../model/automation/classificationcommand.cpp
        ../model/automation/imageloadcommand.h
        ../model/automation/imageloadcommand.cpp
        ../model/automation/trainingcommand.h
        ../model/automation/trainingcommand.cpp
        ../model/automation/splitcommand.h
        ../model/automation/splitcommand.cpp
        ../plugins/classificationplugins/classificationpluginmanager.h
        ../plugins/classificationplugins/classificationpluginmanager.cpp
        ../plugins/plugin.h

        ../plugins/imageplugins/imageloaderplugin.h
        ../plugins/imageplugins/imageloaderpluginmanager.h
        ../plugins/imageplugins/imageloaderpluginmanager.cpp
        ../model/pluginusage/progressableplugin.h
        ../model/results/resultsexporter.h
        ../model/results/resultsexporter.cpp

        test_splitcommand.cpp

        test_imageloadcommand.cpp


        test_folderplugin.cpp
        ../plugins/imageplugins/folderplugin/folderplugin.h
        ../plugins/imageplugins/folderplugin/folderplugin.cpp
        ../plugins/imageplugins/folderplugin/folderconfigwidget.h
        ../plugins/imageplugins/folderplugin/folderconfigwidget.cpp



        test_projectmanager.cpp
        ../model/projectmanager.h
        ../model/projectmanager.cpp
        ../plugins/results/classificationresult.cpp
        ../plugins/results/classificationresult.h
        ../plugins/results/trainingresult.cpp
        ../plugins/results/trainingresult.h
        ../plugins/results/result.cpp
        ../plugins/results/result.h

        ../model/results/confusionmatrix.cpp
        ../model/results/confusionmatrix.h
        ../model/results/accuracycurve.cpp
        ../model/results/accuracycurve.h
        ../model/results/genericresultgraphics.cpp
        ../model/results/genericresultgraphics.h
        ../model/results/classificationgraphics.h
        ../model/results/classificationgraphics.cpp
        ../view/results/topaccuraciesview.h
        ../view/results/topaccuraciesview.cpp
        ../model/results/topaccuraciesgraphics.h
        ../model/results/topaccuraciesgraphics.cpp

        ../model/results/resultsprocessor.h
        ../model/results/resultsprocessor.cpp

        ../view/results/trainingresultview.h
        ../view/results/trainingresultview.cpp

        ../view/results/classificationresultview.h
        ../view/results/classificationresultview.cpp


        ../view/results/genericgraphicsview.h
        ../view/results/genericgraphicsview.cpp

         ../view/results/trainingresultswidget.cpp
         ../view/results/trainingresultswidget.h

         ../view/results/genericcomparisonwidget.h
         ../view/results/genericcomparisonwidget.cpp
         ../view/results/savableresultswidget.h


        ../view/utilities/canvas.h
        ../view/utilities/canvas.cpp

         ../view/utilities/popupmenu.h
         ../view/utilities/popupmenu.cpp

        ../view/utilities/imagegallery.h
        ../view/utilities/imagegallery.cpp

        ../view/utilities/imagegallerytree.h
        ../view/utilities/imagegallerytree.cpp

        ../view/utilities/customtablewidget.h
        ../view/utilities/customtablewidget.cpp

        test_imagegallery.cpp

        test_imagegallerytree.cpp

        test_settingsmanager.cpp

        test_classificationcommand.cpp
        test_trainingcommand.cpp

        test_classifier.cpp
        test_trainer.cpp
        test_imageloader.cpp

        test_imageinspectionmodel.cpp

        test_imageloaderpluginmanager.cpp

        test_classificationpluginmanager.cpp

        test_resultsimporter.cpp

        ../model/results/resultsimporter.h
        ../model/results/resultsimporter.cpp


        test_resultgraphics.cpp
        test_filediff.cpp
        ../model/utilities/filediff.h
        ../model/utilities/filediff.cpp
        ../view/utilities/codeeditor.h
        ../view/utilities/codeeditor.cpp
        )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rsc/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../plugins/imageplugins/flickrplugin/flickrapi_photosearch.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../plugins/imageplugins/bingplugin/bingapi_photosearch.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/utilities/difflibparser.py ${CMAKE_CURRENT_BINARY_DIR}/difflibparser.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/utilities/filediff.py ${CMAKE_CURRENT_BINARY_DIR}/filediff.py COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../Resources/Fonts/Inter-Regular.otf ${CMAKE_CURRENT_BINARY_DIR}/Inter-Regular.otf COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/results/confusionmatrix.py ${CMAKE_CURRENT_BINARY_DIR}/confusionmatrix.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/results/accuracycurve.py ${CMAKE_CURRENT_BINARY_DIR}/accuracycurve.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/results/topaccuraciesgraphics.py ${CMAKE_CURRENT_BINARY_DIR}/topaccuraciesgraphics.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../model/results/classificationgraphics.py ${CMAKE_CURRENT_BINARY_DIR}/classificationgraphics.py COPYONLY)

#imageloaderplugin used for testing created here
add_library(ImageLoaderPluginMock MODULE imageloaderpluginmock.h imageloaderpluginmock.cpp)
add_library(ClassificationPluginMock MODULE classificationpluginmock.h classificationpluginmock.cpp  ../plugins/results/trainingresult.cpp   ../plugins/results/classificationresult.cpp ../plugins/results/result.cpp ../model/results/accuracycurve.cpp  ../model/results/confusionmatrix.cpp ../model/results/genericresultgraphics.cpp ../model/results/classificationgraphics.cpp ../view/results/genericgraphicsview.cpp ../model/configurationmanager.cpp ../model/configurationmanager.h)


#add executables
add_executable(Google_Tests_run ${Sources})
add_executable(ImageInspectionModelTest test_imageinspectionmodel.cpp ../model/imageinspectionmodel.h  ../model/imageinspectionmodel.cpp ../model/utilities/mapadapt.h)
add_executable(ImageLoaderPluginManagerTest test_imageloaderpluginmanager.cpp ../plugins/imageplugins/imageloaderpluginmanager.cpp ../plugins/imageplugins/imageloaderpluginmanager.h)
add_executable(GUITest testgui.cpp testgui.h  ../view/importfileswidget.h ../view/importfileswidget.cpp ../view/utilities/tags.hpp ../view/utilities/tags.cpp ../view/utilities/customlistwidget.cpp ../view/utilities/customlistwidget.h)
add_executable(SettingsManagerTest settingsmanagertest.cpp settingsmanagertest.h  ../model/settingsmanager.h ../model/settingsmanager.cpp

    ../plugins/results/classificationresult.cpp
    ../plugins/results/classificationresult.h
    ../plugins/results/trainingresult.cpp
    ../plugins/results/trainingresult.h
    ../plugins/results/result.cpp
    ../plugins/results/result.h

    ../model/results/confusionmatrix.cpp
    ../model/results/confusionmatrix.h
    ../model/results/accuracycurve.cpp
    ../model/results/accuracycurve.h
    ../model/results/genericresultgraphics.cpp
    ../model/results/genericresultgraphics.h
    ../model/results/classificationgraphics.h
    ../model/results/classificationgraphics.cpp
    ../view/results/topaccuraciesview.h
    ../view/results/topaccuraciesview.cpp
    ../model/results/topaccuraciesgraphics.h
    ../model/results/topaccuraciesgraphics.cpp

    ../model/results/resultsprocessor.h
    ../model/results/resultsprocessor.cpp

    ../view/results/trainingresultview.h
    ../view/results/trainingresultview.cpp

    ../view/results/classificationresultview.h
    ../view/results/classificationresultview.cpp

    ../view/results/genericgraphicsview.h
    ../view/results/genericgraphicsview.cpp

    ../view/utilities/canvas.h
    ../view/utilities/canvas.cpp

    ../view/utilities/imagegallery.h
    ../view/utilities/imagegallery.cpp

    ../view/utilities/imagegallerytree.h
    ../view/utilities/imagegallerytree.cpp

    ../view/utilities/customtablewidget.h
    ../view/utilities/customtablewidget.cpp

    ../plugins/classificationplugins/classificationpluginmanager.h
    ../plugins/classificationplugins/classificationpluginmanager.cpp

    ../plugins/imageplugins/imageloaderpluginmanager.h
    ../plugins/imageplugins/imageloaderpluginmanager.cpp

    ../model/configurationmanager.cpp
    ../model/configurationmanager.h)

#Flickrplugin test, cannot be in same executable as other imageloaderplugin because of QT Plugin definition
add_executable(FlickrPluginTest test_flickrplugin.cpp
    ../plugins/imageplugins/flickrplugin/flickrplugin.h
    ../plugins/imageplugins/flickrplugin/flickrplugin.cpp
    ../plugins/imageplugins/flickrplugin/flickrsettings.h
    ../plugins/imageplugins/flickrplugin/flickrsettings.cpp
    ../model/pluginusage/progressableplugin.h
    ../model/pluginusage/progressable.h
    ../model/pluginusage/imageloader.h
    ../model/pluginusage/imageloader.cpp
    ../plugins/imageplugins/imageloaderpluginmanager.cpp
    ../plugins/imageplugins/imageloaderpluginmanager.h)

#Bingplugin test, cannot be in same executable as other imageloaderplugin because of QT Plugin definition
add_executable(BingPluginTest test_bingplugin.cpp
    ../plugins/imageplugins/bingplugin/bingplugin.cpp
    ../plugins/imageplugins/bingplugin/bingplugin.h
    ../plugins/imageplugins/bingplugin/bingsettings.h
    ../plugins/imageplugins/bingplugin/bingsettings.cpp
    ../model/pluginusage/progressableplugin.h
    ../model/pluginusage/progressable.h
    ../model/pluginusage/imageloader.h
    ../model/pluginusage/imageloader.cpp
    ../plugins/imageplugins/imageloaderpluginmanager.cpp
    ../plugins/imageplugins/imageloaderpluginmanager.h)

#add include directory
target_include_directories(Google_Tests_run PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(ImageInspectionModelTest PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(ImageLoaderPluginMock PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(ClassificationPluginMock PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(ImageLoaderPluginManagerTest PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(GUITest PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(SettingsManagerTest PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(FlickrPluginTest PUBLIC ${MY_INCLUDE_DIRECTORIES})
target_include_directories(BingPluginTest PUBLIC ${MY_INCLUDE_DIRECTORIES})


#add test libaries
target_link_libraries(Google_Tests_run gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(ImageInspectionModelTest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(ImageLoaderPluginMock gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(ClassificationPluginMock gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(ImageLoaderPluginManagerTest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(GUITest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(SettingsManagerTest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(FlickrPluginTest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(BingPluginTest gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})



enable_testing()
add_test(Google_Tests_run COMMAND Google_Tests_run)
add_test(ImageInspectionModelTest COMMAND ImageInspectionModelTest)
add_test(ImageLoaderPluginManagerTest COMMAND ImageLoaderPluginManagerTest)
add_test(GUITest COMMAND GUITest)
add_test(SettingsManagerTest COMMAND GUITest)
add_test(FlickrPluginTest COMMAND FlickrPluginTest)
add_test(BingPluginTest COMMAND BingPluginTest)


add_dependencies(ImageLoaderPluginManagerTest ImageLoaderPluginMock)
add_dependencies(Google_Tests_run ImageLoaderPluginMock ClassificationPluginMock)

