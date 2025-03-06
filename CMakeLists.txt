cmake_minimum_required(VERSION 3.16)

project(iccutil VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_CLANG_TIDY "Use clang-tidy during build" OFF)
option(USE_IWYU "Use iwyu during build" OFF)

if (USE_CLANG_TIDY)
	set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

if (USE_IWYU)
	set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use -Xiwyu "--mapping_file=${CMAKE_SOURCE_DIR}/extra/iwyu.imp")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if (MSVC)
	add_compile_options(/W3 /MP)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

if(USE_GIT_INFO)
	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
		OUTPUT_VARIABLE GIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

# Libraries
add_subdirectory(./src/color)
add_subdirectory(./src/core)
add_subdirectory(./src/gui)
add_subdirectory(./src/icc)
add_subdirectory(./src/icctypes)
add_subdirectory(./src/math)
add_subdirectory(./src/theme)

# Executables
add_subdirectory(./src/iccutil)

if (APPLE)
	install(TARGETS iccutil BUNDLE DESTINATION .)
else()
	install(TARGETS iccutil)
endif()
