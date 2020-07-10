add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core")

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${EXTERNAL_INCLUDE_DIR})
target_include_directories(main PUBLIC ${INTERNAL_INCLUDE_DIR})
target_link_libraries(main glfw core)