set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/icctypes)

add_library(icctypes
	STATIC
	${SRC}/IccDateTimeNumber.cpp
	${INC}/IccDateTimeNumber.h
	${SRC}/IccNumberConverter.cpp
	${INC}/IccNumberConverter.h
)

target_include_directories(icctypes PRIVATE ./include/icctypes)
target_include_directories(icctypes INTERFACE ./include)

target_link_libraries(icctypes core)
