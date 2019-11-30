
file(GLOB_RECURSE IO_MODULE_SOURCES *.h *.c)

add_library(io_module STATIC ${IO_MODULE_SOURCES})

target_link_libraries(io_module stb)
target_link_libraries(io_module assimp)
target_link_libraries(io_module library_commons)
target_link_libraries(io_module cglm)

set_target_properties(io_module PROPERTIES FOLDER "EngineLib")

target_include_directories(io_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})