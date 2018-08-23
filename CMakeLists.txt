cmake_minimum_required (VERSION 2.6)
project (0x1-screenshot)

set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (LIB_DIR "${PROJECT_SOURCE_DIR}/lib")

set (SRCS
	"${SOURCE_DIR}/main.c"
	"${SOURCE_DIR}/retrieve_selected_area.c"
	"${SOURCE_DIR}/take_screenshot.c"
	"${SOURCE_DIR}/upload_screenshot.c"
)

include_directories("${INCLUDE_DIR}")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if (UNIX)
	find_package(X11 REQUIRED)
	find_package(CURL REQUIRED)
	link_libraries(${X11_LIBRARIES})
	link_libraries(${CURL_LIBRARIES})
	include_directories("${LIB_DIR}/stb")
endif (UNIX)

add_executable(0x1-screenshot ${SRCS})