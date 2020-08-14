set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments -Wno-keyword-macro")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY_OUTPUT_DIR})

add_executable(test_core
   test_clock.cpp
   test_object3d.cpp
   test_camera.cpp)

target_include_directories(test_core PUBLIC ${GTEST_INCLUDE_DIR} ${INTERNAL_INCLUDE_DIR})
target_link_libraries(test_core core ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

add_test(NAME core COMMAND test_core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})