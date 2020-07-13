set(TARGETS
   simple_triangle
   3d_boxes)

set(LIBRARIES
   glfw core)

function(CreateBinaryTarget target_name)
   add_executable(${target_name} ${target_name}.cpp)
   target_include_directories(${target_name} PUBLIC ${EXTERNAL_INCLUDE_DIR})
   target_include_directories(${target_name} PUBLIC ${INTERNAL_INCLUDE_DIR})
   target_link_libraries(${target_name} ${LIBRARIES})
endfunction()

foreach(target IN LISTS TARGETS)
   CreateBinaryTarget(${target})
endforeach(target IN LISTS TARGETS)
