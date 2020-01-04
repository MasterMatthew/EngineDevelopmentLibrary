
file(GLOB_RECURSE GRAPHICS_MODULE_SOURCES *.h *.c)

add_library(graphics_module STATIC ${GRAPHICS_MODULE_SOURCES})

target_link_libraries(graphics_module vulkan_module)
target_link_libraries(graphics_module shader_module)
target_link_libraries(graphics_module io_module)
target_link_libraries(graphics_module glfw_module)

set_target_properties(graphics_module PROPERTIES FOLDER "EngineLib")

target_include_directories(graphics_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})