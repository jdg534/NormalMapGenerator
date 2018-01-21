cmake_minimum_required (VERSION 3.10.0)

project (ImageMapGenerator)

# find the Qt5 package

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(source)