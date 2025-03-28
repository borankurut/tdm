cmake_minimum_required(VERSION 3.14)
project(tdm
				VERSION 0.1.0
				DESCRIPTION "3D Math Library"
				LANGUAGES CXX
)

# ----------------------------------------------
# Global configurations
# ----------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # For shared library compatibility

# ----------------------------------------------
# Build type configuration
# ----------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)
if(BUILD_TYPE_UPPER STREQUAL "DEBUG")
	add_compile_definitions(DEBUG)
else()
	add_compile_definitions(RELEASE)
endif()

# ----------------------------------------------
# Main library configuration
# ----------------------------------------------
# Include directories
include_directories(include)

set(MAIN_SRC "examples/main.cpp")

# Find all lib files
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

# Create math library
add_library(math_lib ${LIB_SOURCES})

# Create main executable
add_executable(${PROJECT_NAME} ${MAIN_SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE math_lib)

# ----------------------------------------------
# Testing configuration
# ----------------------------------------------
option(BUILD_TESTS "Build test executable" ON)

if(BUILD_TESTS)
	# Add Catch2 testing framework
	include(FetchContent)
	FetchContent_Declare(
			Catch2
			GIT_REPOSITORY https://github.com/catchorg/Catch2.git
			GIT_TAG        v3.4.0  # Update to latest version as needed
	)
	FetchContent_MakeAvailable(Catch2)

	# Find all test files
	file(GLOB_RECURSE TEST_SOURCES
								"tests/*.cpp"
								"tests/*.cxx"
				)

	# Create test executable
	add_executable(math_tests ${TEST_SOURCES})
	target_link_libraries(math_tests
								PRIVATE
								math_lib
								Catch2::Catch2WithMain
				)

	# Configure CTest
	list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
	include(CTest)
	include(Catch)
	catch_discover_tests(math_tests
								REPORTER "compact"
								PROPERTIES LABELS "AllTests"
				)
endif()

