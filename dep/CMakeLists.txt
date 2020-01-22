#SPDLOG
add_subdirectory(spdlog)

#VULKAN
add_subdirectory(vulkan-headers)
add_subdirectory(vulkan-loader)
set_target_properties(loader_asm_gen_files PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(asm_offset PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(loader-norm PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(loader-opt PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(loader-unknown-chain PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(vulkan PROPERTIES FOLDER "DEPENDENCIES/VULKAN")
set_target_properties(VulkanLoader_generated_source PROPERTIES FOLDER "DEPENDENCIES/VULKAN")

#GLFW
#set(GLFW_VULKAN_STATIC ON)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "DEPENDENCIES/GLFW")
set_target_properties(uninstall PROPERTIES FOLDER "DEPENDENCIES/GLFW")

#SPIRV
set(SPIRV_HEADERS_SKIP_EXAMPLES ON)
set(SPIRV_HEADERS_SKIP_INSTALL ON)
add_subdirectory(SPIRV-headers)
set_target_properties(install-headers PROPERTIES FOLDER "DEPENDENCIES/SPIRV")

set(SKIP_SPIRV_TOOLS_INSTALL ON)
set(SPIRV_SKIP_EXECUTABLES ON)
set(SPIRV_SKIP_TESTS ON)
add_subdirectory(SPIRV-tools)

set_target_properties(spirv-tools-build-version PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spirv-tools-header-DebugInfo PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spv-tools-debuginfo PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spv-tools-spv-amd-gs PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spv-tools-spv-amd-sb PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spv-tools-spv-amd-sevp PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spv-tools-spv-amd-stm PROPERTIES FOLDER "DEPENDENCIES/SPIRV")

set_target_properties(SPIRV-Tools PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(SPIRV-Tools-link PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(SPIRV-Tools-opt PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(SPIRV-Tools-reduce PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(SPIRV-Tools-shared PROPERTIES FOLDER "DEPENDENCIES/SPIRV")

set_target_properties(spirv-tools-vimsyntax PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spirv-tools-pkg-config PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(spirv-tools-shared-pkg-config PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(core_tables PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(enum_string_mapping PROPERTIES FOLDER "DEPENDENCIES/SPIRV")
set_target_properties(extinst_tables PROPERTIES FOLDER "DEPENDENCIES/SPIRV")


#GLSLANG
set(BUILD_EXTERNAL OFF)
set(SKIP_GLSLANG_INSTALL ON)
set(ENABLE_SPVREMAPPER OFF)
set(ENABLE_GLSLANG_BINARIES OFF)
set(ENABLE_OPT OFF)
set(ENABLE_PCH OFF)
set(ENABLE_CTEST OFF)
set(SHADERC_ENABLE_SHARED_CRT ON)
add_subdirectory(glslang)
set_target_properties(glslang PROPERTIES FOLDER "DEPENDENCIES/GLSLANG")
set_target_properties(OGLCompiler PROPERTIES FOLDER "DEPENDENCIES/GLSLANG")
set_target_properties(OSDependent PROPERTIES FOLDER "DEPENDENCIES/GLSLANG")
set_target_properties(SPIRV PROPERTIES FOLDER "DEPENDENCIES/GLSLANG")
set_target_properties(HLSL PROPERTIES FOLDER "DEPENDENCIES/GLSLANG")

#SHADERC
set(SHADERC_SKIP_INSTALL ON)
set(SHADERC_SKIP_TESTS ON)
add_subdirectory(shaderc)
set_target_properties(add-copyright PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(build-version PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(check-copyright PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(glslc PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(glslc_exe PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc_combined_genfile PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc_combined-pkg-config PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc_shared PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc_static-pkg-config PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc_util PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc-online-compile PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(shaderc-pkg-config PROPERTIES FOLDER "DEPENDENCIES/SHADERC")
set_target_properties(testdata PROPERTIES FOLDER "DEPENDENCIES/SHADERC")

#STB
file(GLOB STB_SOURCE stb/*.h stb/*.c)
add_library(stb STATIC ${STB_SOURCE})
set_target_properties(stb 	PROPERTIES 
				FOLDER "DEPENDENCIES/STB")
#LIST(APPEND STB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb")
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/stb")

#ASSIMP
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(INJECT_DEBUG_POSTFIX OFF)
set(ASSIMP_INSTALL_PDB OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ZLIB ON)

add_subdirectory(assimp)

#set_target_properties(assimp PROPERTIES FOLDER "DEPENDENCIES/ASSIMP")

#CGLM
file(GLOB CGLM_HEADERS cglm/include/*.h)

file(GLOB CGLM_CALL_HEADERS cglm/include/call/*.h)
file(GLOB CGLM_SIMD_HEADERS cglm/include/simd/*.h)
file(GLOB CGLM_SIMD_SSE2_HEADERS cglm/include/simd/sse2*.h)
file(GLOB CGLM_AVX_HEADERS cglm/include/avx/*.h)
file(GLOB CGLM_NEON_HEADERS cglm/include/neon/*.h)
file(GLOB CGLM_STRUCT_HEADERS cglm/include/struct/*.h)

file(GLOB CGLM_SOURCES cglm/src/*.c cglm/src/*.h)


add_library(cglm STATIC ${CGLM_SOURCES})
set_target_properties(cglm PROPERTIES FOLDER "DEPENDENCIES/CGLM")
target_include_directories(cglm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/cglm/include")

add_definitions(-DCGLM_DLL)

#VulkanMemoryAllocator
file(GLOB VMA_SOURCES VulkanMemoryAllocator/src/*.cpp VulkanMemoryAllocator/src/*.h)
add_library(vma STATIC ${CGLM_SOURCES})
set_target_properties(vma PROPERTIES FOLDER "DEPENDENCIES/VMA")
target_include_directories(vma PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/VulkanMemoryAllocator/src")