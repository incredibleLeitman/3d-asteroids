cmake_minimum_required(VERSION 3.14)
project(asteroid)

set(CMAKE_CXX_STANDARD 17)

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

add_executable(asteroid main.cpp)

target_link_libraries (asteroid ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})