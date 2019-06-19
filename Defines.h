#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG_OUTPUT true

#ifndef M_PI
    #define M_PI 3.141592653
#endif
#define RAD(x) (((x)*M_PI)/180.)

const int count_stars = 50;
const int count_asteroids = 100;

const int width = 1920;
const int height = 1080;

float inc = 1.00;

const float mouse_speed = 0.2;

const int WORLD_SIZE = 1000;

const GLuint ASTEROID_IMG_ID = 1;
const GLuint EARTH_IMG_ID = 2;
const GLuint COCKPIT_IMG_ID = 3;
const GLuint SUN_IMG_ID = 4;
const GLuint UNIVERSE_IMG_ID = 5;

#endif // DEFINES_H
