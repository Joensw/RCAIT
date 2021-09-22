cmake_minimum_required(VERSION 3.14)
project(googleplugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/library)



find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)

#add_subdirectory(googletest-master)
#add_subdirectory(test)


add_library(googleplugin MODULE
    googleplugin.cpp googleplugin.h googlesettings.cpp googlesettings.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressable.h
)

set_target_properties(googleplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../plugins)

target_include_directories(googleplugin PUBLIC
    ../
    ../../
    ../../../model/pluginusage
    ../../../model
)




target_link_libraries(googleplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)




