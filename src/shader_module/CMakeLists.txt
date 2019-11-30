
file(GLOB_RECURSE SHADER_MODULE_SOURCES *.h *.c)

add_library(shader_module STATIC ${SHADER_MODULE_SOURCES})

target_link_libraries(shader_module shaderc)

set_target_properties(shader_module PROPERTIES FOLDER "EngineLib")

target_include_directories(shader_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})