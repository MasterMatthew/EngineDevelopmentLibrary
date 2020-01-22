
file(GLOB_RECURSE VULKAN_MODULE_SOURCES *.h *.cpp)


add_library(vulkan_module STATIC ${VULKAN_MODULE_SOURCES})

target_compile_definitions(vulkan_module PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_link_libraries(vulkan_module Vulkan::Headers)
target_link_libraries(vulkan_module Vulkan::Vulkan)

target_link_libraries(vulkan_module cglm)

target_link_libraries(vulkan_module library_commons)
target_link_libraries(vulkan_module debug_lib)

target_link_libraries(vulkan_module vma)

set_target_properties(vulkan_module PROPERTIES FOLDER "EngineLib")

target_include_directories(vulkan_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})