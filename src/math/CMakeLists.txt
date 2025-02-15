set(SRC ./src)
set(INC ./include/math)

add_library(math
	STATIC
	${SRC}/Matrix.cpp
	${INC}/Matrix.h
	${SRC}/SafeFuncs.cpp
	${INC}/SafeFuncs.h
	${SRC}/Triangle.cpp
	${INC}/Triangle.h
	${SRC}/Vector.cpp
	${INC}/Vector.h
)

target_include_directories(math PRIVATE ./include/math)
target_include_directories(math INTERFACE ./include)
