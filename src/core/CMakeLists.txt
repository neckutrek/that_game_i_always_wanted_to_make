set(SOURCES
   glad.c)
add_library(core ${SOURCES})
target_include_directories(core PUBLIC ${INTERNAL_INCLUDE_DIR})