set(SOURCES
   clock.cpp)

add_library(core ${SOURCES})
target_include_directories(core PUBLIC ${THIRD_PARTY_INCLUDE_DIR})
target_include_directories(core PUBLIC ${INTERNAL_INCLUDE_DIR})

add_subdirectory("./test")