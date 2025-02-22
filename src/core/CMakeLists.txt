set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/core)

add_library(core
	STATIC
	${INC}/BuildInfo.h
	${SRC}/BuildInfo.cpp
	${INC}/Error.h
	${SRC}/Error.cpp
	${INC}/ExitAssert.h
	${SRC}/ExitAssert.cpp
	${SRC}/Result.cpp
	${INC}/Result.h
	${SRC}/Util.cpp
	${INC}/Util.h
)

if(DEFINED GIT_HASH)
	target_compile_definitions(core PRIVATE GIT_HASH="${GIT_HASH}")
endif()

target_include_directories(core PRIVATE ./include/core)
target_include_directories(core INTERFACE ./include)
