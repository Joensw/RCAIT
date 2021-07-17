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
set(REQUIRED_LIBS Core Gui Widgets LinguistTools Svg SvgWidgets )
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)
set(CMAKE_AUTOUIC_SEARCH_PATHS  ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)


# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name

set(Sources
        test_imageinspectionmodel.cpp
        ../model/imageinspectionmodel.h
        ../model/imageinspectionmodel.cpp)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rsc/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Google_Tests_run ${Sources})
target_link_libraries(Google_Tests_run gtest gtest_main ${REQUIRED_LIBS_QUALIFIED})

enable_testing()
add_test(Google_Tests_run COMMAND Google_Tests_run)
