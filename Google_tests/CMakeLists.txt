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

# 'Google_Tests_run' is the target name

set(Sources
        test_imageinspectionmodel.cpp
        ../model/imageinspectionmodel.h
        ../model/imageinspectionmodel.cpp

        test_task.cpp
        ../model/automation/task.h
        ../model/automation/task.cpp
        ../model/datamanager.h
        ../model/datamanager.cpp
        ../model/settingsmanager.h
        ../model/settingsmanager.cpp
        ../model/modelmanager.h
        ../model/modelmanager.cpp
        ../model/pluginusage/progressable.h
        ../model/pluginusage/progressable.cpp
        ../model/pluginusage/aithread.h
        ../model/pluginusage/aithread.cpp
        ../model/pluginusage/classificationthread.h
        ../model/pluginusage/classificationthread.cpp
        ../model/pluginusage/trainingsthread.h
        ../model/pluginusage/trainingsthread.cpp
        ../model/pluginusage/imagesearchthread.h
        ../model/pluginusage/imagesearchthread.cpp
        ../model/automation/command.h
        ../model/automation/command.cpp
        ../model/automation/classificationcommand.h
        ../model/automation/classificationcommand.cpp
        ../model/automation/imageloadcommand.h
        ../model/automation/imageloadcommand.cpp
        ../model/automation/trainingcommand.h
        ../model/automation/trainingcommand.cpp
        ../plugins/classificationplugins/classificationpluginmanager.h
        ../plugins/classificationplugins/classificationpluginmanager.cpp
        ../plugins/imageplugins/imageloaderpluginmanager.h
        ../plugins/imageplugins/imageloaderpluginmanager.cpp
        ../model/pluginusage/progressableplugin.h
        ../model/pluginusage/progressableplugin.cpp



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
        ../model/results/abstractresultgraphics.cpp
        ../model/results/abstractresultgraphics.h
        )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rsc/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Google_Tests_run ${Sources})
target_link_libraries(Google_Tests_run gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})

enable_testing()
add_test(Google_Tests_run COMMAND Google_Tests_run)
