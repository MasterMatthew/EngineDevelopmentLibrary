
file(GLOB_RECURSE GRAPHICS_SOURCES *.h *.cpp)

add_library(graphics STATIC ${GRAPHICS_SOURCES})

target_link_libraries(graphics graphics_module)
target_link_libraries(graphics stb)
target_link_libraries(graphics assimp)
target_link_libraries(graphics cglm)

set_target_properties(graphics PROPERTIES FOLDER "EngineFramework" CXX_STANDARD 17)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})