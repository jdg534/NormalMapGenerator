cmake_minimum_required (VERSION 3.10.0)

file(GLOB_RECURSE SourceFiles *.h *.cpp)

add_executable(ImageMapGenExe ${SourceFiles})


# make sure that ImageMapGenExe has access to the include directories and libraries


target_link_libraries(ImageMapGenExe Qt5::Widgets)

IF(WIN32)
	SET(TargetDlls "Qt5Core.dll;Qt5Cored.dll;Qt5Gui.dll;Qt5Guid.dll;Qt5Widgets.dll;Qt5Widgetsd.dll")
	FOREACH(TargetDll ${TargetDlls})
		file(COPY $ENV{Qt5_DIR}/../../../bin/${TargetDll} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDFOREACH()
ENDIF()