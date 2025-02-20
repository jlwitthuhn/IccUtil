set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/icc)

add_library(icc
	STATIC
	${SRC}/IccDataType.cpp
	${INC}/IccDataType.h
	${SRC}/IccFileBody.cpp
	${INC}/IccFileBody.h
	${SRC}/IccFileHeader.cpp
	${INC}/IccFileHeader.h
	${SRC}/IccFileTagEntry.cpp
	${INC}/IccFileTagEntry.h
	${SRC}/IccProfile.cpp
	${INC}/IccProfile.h
	${SRC}/Util.cpp
	${INC}/Util.h
)

target_include_directories(icc PRIVATE ./include/icc)
target_include_directories(icc INTERFACE ./include)

target_link_libraries(icc core icctypes)
