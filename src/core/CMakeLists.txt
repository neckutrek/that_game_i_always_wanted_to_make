set(SOURCES
   glad.c
   shader_builder.cpp)
add_library(core ${SOURCES})
target_include_directories(core PUBLIC ${INTERNAL_INCLUDE_DIR})