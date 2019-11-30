
file(GLOB_RECURSE LIBRARY_COMMONS_HEADERS *.h)

add_library(library_commons INTERFACE)

target_include_directories(library_commons INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(library_commons_ SOURCES ${LIBRARY_COMMONS_HEADERS})
set_target_properties(library_commons_ PROPERTIES FOLDER "EngineLib")
set_target_properties(library_commons_ PROPERTIES LANGUAGE C LINKER_LANGUAGE C)