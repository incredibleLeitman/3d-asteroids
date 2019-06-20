#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG_OUTPUT true

#ifndef M_PI
    #define M_PI 3.141592653
#endif
#define RAD(x) (((x)*M_PI)/180.)

const int count_stars = 50;
const int count_asteroids = 500;

const int width = 1920;
const int height = 1080;

float inc = .5f;

const float mouse_speed = 0.2;

const int WORLD_SIZE = 2000;
const float STAR_MIN_SIZE = 0.1f;
const float STAR_MAX_SIZE = 0.15f;
const float ASTEROID_MIN_SIZE = 0.5f;
const float ASTEROID_MAX_SIZE = 6.0f;

const double MIN_FOV = 70.0;
const double MAX_FOV_ADD = 40.0;

const GLuint ASTEROID_IMG_ID = 1;
const GLuint EARTH_IMG_ID = 2;
const GLuint COCKPIT_IMG_ID = 3;
const GLuint SUN_IMG_ID = 4;
const GLuint UNIVERSE_IMG_ID = 5;

GLfloat sunLightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat sunLightDiffuse[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat sunLightAmbient[] = { 0.7, 0.7, 1.0, 1.0 };

#endif // DEFINES_H
