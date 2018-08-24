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
	"${SOURCE_DIR}/cfg/cfg_init.c"
	"${SOURCE_DIR}/cfg/cfg_key_get_value.c"
	"${SOURCE_DIR}/cfg/cfg_key_get_default_value.c"
	"${SOURCE_DIR}/cfg/cfg_destroy.c"
)

include_directories("${INCLUDE_DIR}")
include_directories("${LIB_DIR}/list/include")

file(GLOB UTILS_SRC "${LIB_DIR}/utils/src/*.c")
add_library(utils STATIC ${UTILS_SRC})
target_include_directories(utils PUBLIC "${LIB_DIR}/utils/include")
file(GLOB LIST_SRC "${LIB_DIR}/list/src/*.c")
add_library(list STATIC ${LIST_SRC})
target_include_directories(list PUBLIC "${LIB_DIR}/list/include")

find_package(CURL REQUIRED)
link_libraries(${CURL_LIBRARIES})

if (UNIX)
	find_package(X11 REQUIRED)
	link_libraries(${X11_LIBRARIES})
	include_directories("${LIB_DIR}/stb")
endif (UNIX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(0x1-screenshot ${SRCS})
target_link_libraries(0x1-screenshot utils)
target_link_libraries(0x1-screenshot list)