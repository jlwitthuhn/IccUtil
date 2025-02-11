set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/icc)

add_library(icc
	STATIC
	${SRC}/IccProfile.cpp
	${INC}/IccProfile.h
)

target_include_directories(icc PRIVATE ./include/icc)
target_include_directories(icc INTERFACE ./include)
