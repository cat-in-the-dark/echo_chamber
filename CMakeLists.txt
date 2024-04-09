cmake_minimum_required(VERSION 3.11)
project(echo_test CXX)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build raylib-cpp examples

if (NOT MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-multichar")
endif()

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
endif ()

add_subdirectory(libs/raylib)

add_subdirectory(libs/raygui/projects/CMake)

add_subdirectory(libs/raylib-cpp)

add_executable(${PROJECT_NAME}
    src/screens/landscape_screen.cpp
    src/main.cpp
    src/utils/collisions.cpp
    src/utils/perlin.cpp
    src/utils/render.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    libs/raylib-cpp/include
    )

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui)
