cmake_minimum_required(VERSION 3.14)
project(flickrplugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/library)



find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)

enable_testing()
#add_subdirectory(googletest-master)
#add_subdirectory(test)


add_library(flickrplugin MODULE
    flickrplugin.cpp flickrplugin.h flickrsettings.cpp flickrsettings.h ../../../model/pluginusage/progressableplugin.h ../../../model/pluginusage/progressableplugin.cpp ../../../model/pluginusage/progressable.h ../../../model/pluginusage/progressable.cpp
)

set_target_properties(flickrplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../plugins)

target_include_directories(flickrplugin PUBLIC
    ../
    ../../../model/pluginusage
)




target_link_libraries(flickrplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)




