set(CMAKE_AUTOMOC ON)

set(SRC ./src)
set(INC ./include/icctypes)

add_library(icctypes
	STATIC
	${SRC}/IccDateTimeNumber.cpp
	${INC}/IccDateTimeNumber.h
	${SRC}/IccMultiLocalizedUnicodeType.cpp
	${INC}/IccMultiLocalizedUnicodeType.h
	${SRC}/IccNumberConverter.cpp
	${INC}/IccNumberConverter.h
	${SRC}/IccSignatureType.cpp
	${INC}/IccSignatureType.h
	${SRC}/IccTextDescriptionType.cpp
	${INC}/IccTextDescriptionType.h
	${SRC}/IccTextType.cpp
	${INC}/IccTextType.h
	${SRC}/IccXyzNumber.cpp
	${INC}/IccXyzNumber.h
	${SRC}/IccXyzType.cpp
	${INC}/IccXyzType.h
)

target_include_directories(icctypes PRIVATE ./include/icctypes)
target_include_directories(icctypes INTERFACE ./include)

target_link_libraries(icctypes core)
