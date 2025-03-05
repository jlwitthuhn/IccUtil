set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/gui)

add_library(gui
	STATIC
	${SRC}/ChromaticityDiagramWidget.cpp
	${SRC}/ChromaticityDiagramWidget.h
	${SRC}/ChromaticityTopWidget.cpp
	${SRC}/ChromaticityTopWidget.h
	${SRC}/ConvertColorWidget.cpp
	${SRC}/ConvertColorWidget.h
	${SRC}/IccMultiLocalizedUnicodeTypeDetailsWidget.cpp
	${SRC}/IccMultiLocalizedUnicodeTypeDetailsWidget.h
	${SRC}/IccTextTypeDetailsWidget.cpp
	${SRC}/IccTextTypeDetailsWidget.h
	${SRC}/IccXyzTypeDetailsWidget.cpp
	${SRC}/IccXyzTypeDetailsWidget.h
	${SRC}/MainWindow.cpp
	${INC}/MainWindow.h
	${SRC}/ProfileDetailsWidget.cpp
	${SRC}/ProfileDetailsWidget.h
	${SRC}/Util.cpp
	${SRC}/Util.h
)

target_include_directories(gui PRIVATE ./include/gui)
target_include_directories(gui INTERFACE ./include)

target_link_libraries(gui color math icc)
target_link_libraries(gui Qt6::Widgets)
