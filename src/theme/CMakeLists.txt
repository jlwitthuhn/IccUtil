set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/theme)

add_library(theme
	STATIC
	${SRC}/DarkTheme.cpp
	${INC}/DarkTheme.h
)

target_include_directories(theme PRIVATE ./include/theme)
target_include_directories(theme INTERFACE ./include)

target_link_libraries(theme Qt6::Widgets)
