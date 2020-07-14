set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY_OUTPUT_DIR})

add_executable(test_core
   test_clock.cpp)

target_include_directories(test_core PUBLIC ${GTEST_INCLUDE_DIR} ${INTERNAL_INCLUDE_DIR})
target_link_libraries(test_core core ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

add_test(NAME core COMMAND test_core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})