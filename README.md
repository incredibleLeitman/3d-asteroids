# 3d-asteroids

![Screenshot](resources/screenshot.png?raw=true "Screenshot")

3D Asteroids game made with classic OpenGL and GLUT with a tree-based Object structure inspired by Godot.

## Controls

### Angular movement

W, S: Pitch

A, D: Roll

Q, E: Yaw

Mouse click and drag: Rotate head inside cockpit

### Linear movement

I, K: Forward / Backwards

J, L: Left / Right

U, O: Up / Down

## Building

The project can be opened, edited and built in CLion. Alternatively, CMake or Make (using the CMake-generated Makefile in cmake-build-debug) works too.

Also added a project file for visual studio support (MVS2019 tested)

## "player collided with asteroidXXXCollider"

"Yes, the exception which is thrown when crashing against an asteroid is intentional - there's no game over screen."
