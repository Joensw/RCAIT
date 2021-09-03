cmake_minimum_required(VERSION 3.5)
project(RCAIT LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64\\lib\\cmake")
#set(CMAKE_PREFIX_PATH "D:\\Qt\\6.2.0\\mingw81_64\\lib\\cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets LinguistTools Svg SvgWidgets )
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)

set(ALL_PROJECT_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        model model/automation model/pluginusage model/results model/utilities
        view view/results view/utilities
        controller
        Resources
        plugins plugins/classificationplugins plugins/imageplugins plugins/results
        )

set(CMAKE_AUTOUIC_SEARCH_PATHS  ${ALL_PROJECT_DIRS})
include_directories(${ALL_PROJECT_DIRS})

file(GLOB_RECURSE SOURCE_FILES
        "model/*"
        "view/*"
        "controller/*"
        "plugins/*"
        "Resources/*"
        )

list(FILTER SOURCE_FILES EXCLUDE REGEX "/test/.*" )
list(FILTER SOURCE_FILES EXCLUDE REGEX "/flickrplugin/.*" )
list(FILTER SOURCE_FILES EXCLUDE REGEX "/folderplugin/.*" )
list(FILTER SOURCE_FILES EXCLUDE REGEX "/bingplugin/.*" )
list(FILTER SOURCE_FILES EXCLUDE REGEX "/mmclassificationplugin/.*")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Fonts/Inter-Regular.otf ${CMAKE_CURRENT_BINARY_DIR}/Inter-Regular.otf COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/model/results/confusionmatrix.py ${CMAKE_CURRENT_BINARY_DIR}/confusionmatrix.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/model/results/accuracycurve.py ${CMAKE_CURRENT_BINARY_DIR}/accuracycurve.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/model/results/topaccuraciesgraphics.py ${CMAKE_CURRENT_BINARY_DIR}/topaccuraciesgraphics.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/model/results/classificationgraphics.py ${CMAKE_CURRENT_BINARY_DIR}/classificationgraphics.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/imageplugins/flickrplugin/flickrapi_photosearch.py ${CMAKE_CURRENT_BINARY_DIR}/flickrapi_photosearch.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/imageplugins/bingplugin/bingapi_photosearch.py ${CMAKE_CURRENT_BINARY_DIR}/bingapi_photosearch.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/imageplugins/flickrplugin/test.py ${CMAKE_CURRENT_BINARY_DIR}/test.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/classificationplugins/mmclassificationplugin/mmclassification_preview_pipeline.py ${CMAKE_CURRENT_BINARY_DIR}/mmclassification_preview_pipeline.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/classificationplugins/mmclassificationplugin/mmclassification_test.py ${CMAKE_CURRENT_BINARY_DIR}/mmclassification_test.py COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/plugins/classificationplugins/mmclassificationplugin/mmclassification_train.py ${CMAKE_CURRENT_BINARY_DIR}/mmclassification_train.py COPYONLY)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

file(GLOB TS_FILES
        "languages/*.ts"
        )

#qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
qt_add_translation(QM_FILES ${TS_FILES})

set(SRCS "${CMAKE_CURRENT_SOURCE_DIR}/RCAIT.rc")

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${TS_FILES}
        ${QM_FILES}
        ${SRCS}
        )

target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

#enable_testing()
#add_subdirectory(lib/googletest-master)
#add_subdirectory(model/test)
add_subdirectory(Google_tests)
add_subdirectory(plugins/imageplugins/flickrplugin)
add_subdirectory(plugins/imageplugins/bingplugin)
add_subdirectory(plugins/imageplugins/folderplugin)
add_subdirectory(plugins/classificationplugins/mmclassificationplugin)
