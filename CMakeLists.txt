cmake_minimum_required(VERSION 3.19)

# ########################################################
# PROJECT
# ########################################################
project(GUTIL
	VERSION 1.0
	LANGUAGES CXX
	)

# ########################################################
# TARGET
# ########################################################
add_library(GUTIL-static STATIC)

# ########################################################
# COMPILER
# ########################################################
set(CCFLAGS -Wall -Wextra)
set(MSVCFLAGS /W3)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_options(GUTIL-static PRIVATE ${CCFLAGS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(GUTIL-static PRIVATE ${MSVCFLAGS})
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MinGW")
		target_compile_options(GUTIL-static PRIVATE ${CCFLAGS})
	endif()
endif()	

# ########################################################
# LINKING
# ########################################################
target_sources(GUTIL-static PRIVATE
	"src/GUTIL_file.cc"
	"src/GUTIL_time.cc"
	)
target_include_directories(GUTIL-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
