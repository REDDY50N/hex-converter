set(LIB_NAME "CoreLib")

add_library(${LIB_NAME} STATIC
        NumberBase.cpp
        NumberBase.h
        NumberFormatter.cpp
        NumberFormatter.h
        NumberParser.cpp
        NumberParser.h
)

target_link_libraries(${LIB_NAME} Qt::Core)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)