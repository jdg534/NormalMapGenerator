cmake_minimum_required (VERSION 3.10.0)

project (ImageMapGenerator)

# find the Qt5 package

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add maths library
add_subdirectory(JoshMath)

add_subdirectory(source)