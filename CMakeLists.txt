cmake_minimum_required(VERSION 3.13)
project(OpenGLApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Wildcard for all .cpp files in src/ (CONFIGURE_DEPENDS detects added/removed files)
set(SOURCES
    src/main.cpp 
    src/program.cpp
    src/renderer.cpp
    src/math.cpp
    src/camera.cpp
)


add_executable(OpenGLApp ${SOURCES})
target_include_directories(OpenGLApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Link OpenGL (note: you'll also want GLFW, SDL2, or GLAD for a window/context)
target_link_libraries(OpenGLApp PRIVATE 
    OpenGL::GL
    glfw
    GLEW::GLEW
)

# Ensure the executable outputs directly into the build root folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

