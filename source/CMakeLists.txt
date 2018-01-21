cmake_minimum_required (VERSION 3.10.0)

file(GLOB_RECURSE SourceFiles *.h *.cpp)

add_executable(ImageMapGenExe ${SourceFiles})
