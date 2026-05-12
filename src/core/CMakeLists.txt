set(LIB_NAME "CoreLib")

add_library(${LIB_NAME} STATIC
        NumberBase.cpp
        NumberBase.h
        NumberFormatter.cpp
        NumberFormatter.h
        NumberParser.cpp
        NumberParser.h
        ConversionService.cpp
        ConversionService.h
        ByteInspector.cpp
        ByteInspector.h
        ConversionResult.cpp
        ConversionResult.h
)

target_link_libraries(${LIB_NAME} PUBLIC Qt::Core)
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# -----------------------------------------------
# UNIT TESTING
# -----------------------------------------------

# HINT:
# A good pratice is to keep tests a close a possible to the code thats is tested
# For several reasons like include paths, forget to implement them or just ignore the test dir

if(BUILD_TESTING)

    # Add new tests here and they will be automatically added to the custom target below ...
    set(TEST_NAMES
            NumberBase_Test
            NumberFormatter_Test
            NumberParser_Test
            ConversionService_Test
            ByteInspector_Test
    )


    # Collect all test names
    foreach(test_name IN LISTS TEST_NAMES)
        add_executable(${test_name} ${test_name}.cpp)
        target_link_libraries(${test_name} PRIVATE CoreLib Catch2::Catch2WithMain)
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()

    # Build command for custom target with all tests
    set(RUN_COMMANDS "")
    foreach(test_name IN LISTS TEST_NAMES)
        list(APPEND RUN_COMMANDS COMMAND ${test_name})
    endforeach()

    # Custom target: run all lib tests
    add_custom_target(run-core-lib-tests
            ${RUN_COMMANDS}
            DEPENDS ${TEST_NAMES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Running all core library tests..."
    )

endif()