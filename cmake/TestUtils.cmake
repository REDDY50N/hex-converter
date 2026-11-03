# Helper function to add a Catch2 test target easily
function(add_catch2_test test_name)

    # Generate test names and test file name (e.g., Test_NumberBase and NumberBase_Test.cpp)
    set(test_target "Test_${test_name}")
    set(test_source "${test_name}_Test.cpp")

    # Add the test executable and link it with the CoreLib and Catch2
    add_executable(${test_target} ${test_source})
    target_link_libraries(${test_target} PRIVATE CoreLib Catch2::Catch2WithMain)
    add_test(NAME ${test_target} COMMAND ${test_target})

    # Optional: Enable code coverage if the option is set
    if(ENABLE_COVERAGE)
        target_compile_options(${test_target} PRIVATE --coverage)
        target_link_options(${test_target} PRIVATE --coverage)
    endif()

    # Target-Namen nach "oben" propagieren für das Custom Target
    set_property(GLOBAL APPEND PROPERTY CORE_TEST_TARGETS ${test_target})
endfunction()