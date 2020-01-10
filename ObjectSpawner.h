#pragma once
#ifndef OBJECT_SPAWNER_H
#define OBJECT_SPAWNER_H

#include "BaseObjects/RenderObject.h"

/// Provides shortcuts for creating typical objects
class ObjectSpawner {
public:
    ObjectSpawner() = default;

    virtual ~ObjectSpawner() = default;

    /// Create a stationary, rotating sphere (e.g. planets, asteroids)
    KinematicObject* createSphere(std::string name, GLuint texId,
        GLfloat r, GLfloat g, GLfloat b,
        GLdouble radius_min, GLdouble radius_max,
        float rotspeed, float rot_x, float rot_y, float rot_z);

    /// Create a stationary, rotating cube
    KinematicObject* createCube(std::string name, GLuint texId,
        GLfloat r, GLfloat g, GLfloat b,
        GLdouble dim_min, GLdouble dim_max,
        float rotspeed, float rot_x, float rot_y, float rot_z);
};

#endif // OBJECT_SPAWNER_H
