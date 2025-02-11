cmake_minimum_required(VERSION 3.16)

project(iccutil VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if (MSVC)
	add_compile_options(/W3 /MP)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

# Libraries
add_subdirectory(./src/color)
add_subdirectory(./src/gui)
add_subdirectory(./src/icc)
add_subdirectory(./src/math)
add_subdirectory(./src/theme)

# Executables
add_subdirectory(./src/iccutil)

if (APPLE)
	install(TARGETS iccutil BUNDLE DESTINATION .)
else()
	install(TARGETS iccutil)
endif()
