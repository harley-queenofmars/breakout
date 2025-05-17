cmake_minimum_required(VERSION 3.6)
project(breakout)
set ( VERSION 0.0.1 )
set ( RELEASE_NAME breakout )
set ( APP_NAME "index" )
set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)

add_subdirectory ( external/corefw )
add_subdirectory ( external/corefx )

add_executable( ${APP_NAME} 
    src/main.c 
    src/Demo.c
    src/Wren.c
    src/Registry.c
    src/BallObject.c 
    src/Collision.c 
    src/GameLevel.c 
    src/GameObject.c 
    src/Particle.c 
    src/ParticleGenerator.c 
    external/wren/deps/wren/src/vm/wren_compiler.c
    external/wren/deps/wren/src/vm/wren_core.c
    external/wren/deps/wren/src/vm/wren_debug.c
    external/wren/deps/wren/src/optional/wren_opt_meta.c
    external/wren/deps/wren/src/optional/wren_opt_random.c
    external/wren/deps/wren/src/vm/wren_primitive.c
    external/wren/deps/wren/src/vm/wren_utils.c
    external/wren/deps/wren/src/vm/wren_value.c
    external/wren/deps/wren/src/vm/wren_vm.c
    ${SOURCE} )

include_directories( external/stb )
include_directories( external/wren/deps/wren/include )
include_directories( external/wren/deps/wren/src/vm )
include_directories( external/wren/deps/wren/src/optional )
include_directories( external/blocksruntime/BlocksRuntime )

target_include_directories(${APP_NAME} PUBLIC /home/darko/Documents/GitHub/emsdk/upstream/emscripten/cache/sysroot/include/)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c23") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o index.html") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s MAXIMUM_MEMORY=4GB") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ALLOW_MEMORY_GROWTH") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s FULL_ES3") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --preload-file=../Resources") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --shell-file=../src/template.html") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/home/darko/Documents/GitHub/emsdk/upstream/emscripten/cache/sysroot/include") 

