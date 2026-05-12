set(LIB_NAME "CoreLib")

add_library(${LIB_NAME} STATIC
        NumberBase.cpp
        NumberBase.h
        NumberFormatter.cpp
        NumberFormatter.h
        NumberParser.cpp
        NumberParser.h
)

target_link_libraries(${LIB_NAME} PUBLIC Qt::Core)
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# HINT:
# A good pratice is to keep tests a close a possible to the code thats is tested
# For several reasons like include paths, forget to implement them or just ignore the test dir
add_executable(Test_NumberBase NumberBase_Test.cpp)
target_link_libraries(Test_NumberBase PRIVATE CoreLib Catch2::Catch2WithMain)
add_test(NAME Test_NumberBase COMMAND Test_NumberBase)

add_executable(Test_NumberFormater NumberFormatter_Test.cpp)
target_link_libraries(Test_NumberFormater PRIVATE CoreLib Catch2::Catch2WithMain)
add_test(NAME Test_NumberFormater COMMAND Test_NumberFormater)

add_executable(Test_NumberParser NumberParser_Test.cpp)
target_link_libraries(Test_NumberParser PRIVATE CoreLib Catch2::Catch2WithMain)
add_test(NAME Test_NumberParser COMMAND Test_NumberParser)


add_custom_target(run-core-lib-tests
        COMMAND Test_NumberBase
        COMMAND Test_NumberFormater
        COMMAND Test_NumberParser
        DEPENDS Test_NumberBase Test_NumberFormater Test_NumberParser
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running all tests..."
)