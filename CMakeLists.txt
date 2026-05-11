cmake_minimum_required(VERSION 3.30)


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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(warnings "-Wall -Wextra -Wpedantic")

# ----------------------------------------------
# QT SETUP
# ----------------------------------------------
set(CMAKE_PREFIX_PATH ~/Qt/6.9.1/gcc_64/lib/cmake/Qt6)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ----------------------------------------------
# FIND PACKAGES
# ----------------------------------------------
find_package(Qt6 COMPONENTS Core REQUIRED)

# ----------------------------------------------
# TARGET SETUP
# ----------------------------------------------
add_subdirectory(src)
#add_executable(${EXEC_NAME} main.cpp)
#target_link_libraries(${EXEC_NAME} Qt::Core)
#
