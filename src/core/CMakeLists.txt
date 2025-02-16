set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/core)

add_library(core
	STATIC
	${SRC}/Dummy.cpp
	${INC}/Error.h
	${SRC}/Error.cpp
	${INC}/Error.h
	${SRC}/Result.cpp
	${INC}/Result.h
)

target_include_directories(core PRIVATE ./include/core)
target_include_directories(core INTERFACE ./include)
