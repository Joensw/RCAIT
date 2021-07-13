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
set(REQUIRED_LIBS Core Gui Widgets Charts LinguistTools Svg SvgWidgets QuickControls2)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts Qt6::Svg Qt6::SvgWidgets Qt6::QuickControls2)

set(CMAKE_AUTOUIC_SEARCH_PATHS  ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
        model model/automation model/pluginusage model/results
        view view/imageinspection view/results
        controller
        Resources
        plugins plugins/imageplugins plugins/results
        )

file(GLOB_RECURSE SOURCE_FILES_A
        "model/*"
        "view/*"
        "controller/*"
        "plugins/*"
        "Resources/*"
        )

file(GLOB SOURCE_FILES_B
        "*.qrc"
        "*.ui"
        "*.py"
        )

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/model/results/confusionmatrix.py ${CMAKE_CURRENT_BINARY_DIR}/confusionmatrix.py COPYONLY)

set(SOURCE_FILES ${SOURCE_FILES_A} ${SOURCE_FILES_B})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

file(GLOB TS_FILES
        "languages/*.ts"
        )

#qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
qt_add_translation(QM_FILES ${TS_FILES})

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${TS_FILES}
        ${QM_FILES}
       # ${SRCS} RCAIT.rc
        )

target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()