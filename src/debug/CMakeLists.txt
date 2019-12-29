
file(GLOB_RECURSE DEBUG_HEADERS *.h *.cpp)

add_library(debug_lib STATIC ${DEBUG_HEADERS})

target_link_libraries(debug_lib spdlog)

target_include_directories(debug_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(debug_lib PROPERTIES FOLDER "EngineLib")
set_target_properties(debug_lib PROPERTIES LANGUAGE CXX LINKER_LANGUAGE CXX)