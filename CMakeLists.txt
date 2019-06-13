cmake_minimum_required(VERSION 3.14)
project(asteroid)

set(CMAKE_CXX_STANDARD 17)

# set to fixed dir --> or just add environment variables
#if (WIN32)
#if (NOT GLUT_INCLUDE_DIR)
#    set(GLUT_INCLUDE_DIR dir/to/glu)
#endif()

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

add_executable(asteroid main.cpp Object.cpp Object.h tga.h tga.cpp Defines.h RandomRange.h TextureManager.h TextureManager.cpp Collidable.cpp Collidable.h CollidableObject.cpp CollidableObject.h)

target_link_libraries (asteroid ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})