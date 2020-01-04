
file(GLOB_RECURSE GLFW_MODULE_SOURCES *.h *.c)

add_library(glfw_module STATIC ${GLFW_MODULE_SOURCES})

target_link_libraries(glfw_module glfw)

set_target_properties(glfw_module PROPERTIES FOLDER "EngineLib")

target_include_directories(glfw_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})