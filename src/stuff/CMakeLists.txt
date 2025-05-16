cmake_minimum_required(VERSION 3.5)
project(wren)
set ( VERSION 0.0.1 )
set ( RELEASE_NAME wren )
set ( APP_NAME "index" )
set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)

add_subdirectory ( libs/corefw )
# add_subdirectory ( libs/corefx )
add_subdirectory ( libs/wren )
add_executable( ${APP_NAME} 
    src/main.c 
    ${SOURCE} )

    
# include_directories( external/stb )
include_directories( libs/wren/include )
include_directories( libs/wren/src/vm )
include_directories( libs/wren/src/optional )

target_include_directories(${APP_NAME} PUBLIC /home/darko/Documents/GitHub/emsdk/upstream/emscripten/cache/sysroot/include/)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c23") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o index.html") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s FULL_ES3") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --preload-file=../Resources") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --shell-file=../src/template.html") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/home/darko/Documents/GitHub/emsdk/upstream/emscripten/cache/sysroot/include") 

