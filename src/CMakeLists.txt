#LIBRARY MODULES / ABSTRACTION LAYER
add_subdirectory(library_commons)

add_subdirectory(io_module)
add_subdirectory(vulkan_module)
add_subdirectory(shader_module)
add_subdirectory(graphics_module)

#FRAMEWORK
add_subdirectory(graphics)

#DEMOS
add_subdirectory(demo)
