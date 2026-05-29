cmake_minimum_required(VERSION 3.16...3.30)

# ----------------------------------------------
# PROJECT SETUP
# ----------------------------------------------
project(hex-converter
        VERSION 0.0.1
        DESCRIPTION "Convert between hex, dec and bin"
        LANGUAGES CXX)
set(EXEC_NAME ${PROJECT_NAME})

# ----------------------------------------------
# COMPILER SETUP
# ----------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# HINT: Turn ON to fix compiler warnings (Only supported in CMake >= 3.24)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)



# ----------------------------------------------
# QT SETUP
# ----------------------------------------------
set(CMAKE_PREFIX_PATH ~/Qt/6.9.1/gcc_64/lib/cmake/Qt6)
find_package(Qt6 COMPONENTS Core REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# -----------------------------------------------
# CMAKE PACKAGE MANAGER (CPM
# -----------------------------------------------
include(cmake/CPM.cmake)
CPMAddPackage(NAME Catch2    GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"   GIT_TAG "v3.8.1")

# ----------------------------------------------
# TARGET SETUP
# ----------------------------------------------
# bin dir: https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_subdirectory(src)

# -----------------------------------------------
# UNIT TESTING
# -----------------------------------------------
# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
OPTION(BUILD_TESTING "Enable unit testing" ON)
if(BUILD_TESTING)
    include(CTest)
    # we can't use auto detect tests now - does not work properly for now
    #include(Catch) fails - https://github.com/catchorg/Catch2/pull/2130
    # work around is to specify the full path
endif()

# -----------------------------------------------
# INSTALLATION
# -----------------------------------------------
install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
