add_executable(main glad.c main.cpp)
target_include_directories(main PUBLIC ${PROJECT_INCLUDE_DIR})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(main glfw)