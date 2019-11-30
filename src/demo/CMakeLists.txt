
file(GLOB_RECURSE DEMO_SOURCES *.h *.cpp)

add_executable(demo ${DEMO_SOURCES})

target_link_libraries(demo graphics)

set_target_properties(demo PROPERTIES FOLDER "Demos" CXX_STANDARD 17)

