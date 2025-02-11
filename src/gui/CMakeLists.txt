set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/gui)

add_library(gui
	STATIC
	${SRC}/ChromaticityWidget.cpp
	${INC}/ChromaticityWidget.h
	${SRC}/MainWindow.cpp
	${INC}/MainWindow.h
)

target_include_directories(gui PRIVATE ./include/gui)
target_include_directories(gui INTERFACE ./include)

target_link_libraries(gui color math icc)
target_link_libraries(gui Qt6::Widgets)
