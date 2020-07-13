set(SOURCES
   shader_builder.cpp)

add_library(gfx ${SOURCES})
target_include_directories(gfx PUBLIC ${THIRD_PARTY_INCLUDE_DIR})
target_include_directories(gfx PUBLIC ${INTERNAL_INCLUDE_DIR})