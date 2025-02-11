set(SRC ./src)
set(INC ./include/color)

add_library(color
	STATIC
	${SRC}/RgbColor.cpp
	${INC}/RgbColor.h
	${SRC}/SimpleColorConverter.cpp
	${INC}/SimpleColorConverter.h
	${SRC}/XyChromaticity.cpp
	${INC}/XyChromaticity.h
	${SRC}/XyzFloatColor.cpp
	${INC}/XyzFloatColor.h
	${SRC}/XyzSpace.cpp
	${INC}/XyzSpace.h
)

target_include_directories(color PRIVATE ./include/color)
target_include_directories(color INTERFACE ./include)

target_link_libraries(color math)
