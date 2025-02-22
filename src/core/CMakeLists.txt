set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/core)

add_library(core
	STATIC
	${INC}/Error.h
	${SRC}/Error.cpp
	${INC}/ExitAssert.h
	${SRC}/ExitAssert.cpp
	${SRC}/Result.cpp
	${INC}/Result.h
	${SRC}/Util.cpp
	${INC}/Util.h
)

target_include_directories(core PRIVATE ./include/core)
target_include_directories(core INTERFACE ./include)
