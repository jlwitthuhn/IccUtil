set(SRC
	./src/main.cpp
)

if (APPLE)
	add_executable(iccutil
		MACOSX_BUNDLE
		${SRC}
	)
elseif (WIN32)
	add_executable(iccutil
		WIN32
		${SRC}
	)
else()
	add_executable(iccutil
		${SRC}
	)
endif()

target_link_libraries(iccutil core gui theme)
target_link_libraries(iccutil Qt6::Widgets)
