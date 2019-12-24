
file(GLOB_RECURSE DEBUG_HEADERS *.h *.c)

add_library(debug STATIC ${DEBUG_HEADERS})

target_include_directories(debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(debug PROPERTIES FOLDER "EngineLib")
set_target_properties(debug PROPERTIES LANGUAGE C LINKER_LANGUAGE C)