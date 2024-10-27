cmake_minimum_required(VERSION 3.29)
project(opengl_test)

set(CMAKE_CXX_STANDARD 20)

# adding the dirs.
add_subdirectory(./src/)
add_subdirectory(./vendor/glfw)

# setting up glfw
target_link_libraries(${PROJECT_NAME} glfw)

# setting up opengl
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)


