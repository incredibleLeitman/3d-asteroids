cmake_minimum_required(VERSION 3.14)
project(asteroid)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

add_executable(asteroid
        main.cpp
        BaseObjects/Object.cpp
        BaseObjects/Object.h
        Util/tga.h
        Util/tga.cpp
        Defines.h
        Util/RandomRange.h
        Util/TextureManager.h
        Util/TextureManager.cpp
        BaseObjects/Collidable.cpp
        BaseObjects/Collidable.h
        BaseObjects/CollidableObject.cpp
        BaseObjects/CollidableObject.h
        ObjectSpawner.h
        ObjectSpawner.cpp)

target_link_libraries(asteroid ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})