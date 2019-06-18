#pragma once
#ifndef OBJECT_SPAWNER_H
#define OBJECT_SPAWNER_H

#include "BaseObjects/RenderObject.h"

class ObjectSpawner {
public:
    ObjectSpawner() = default;

    virtual ~ObjectSpawner() = default;

    KinematicObject * createSphere(std::string name, int index, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius);

    KinematicObject * createCube(std::string name, int index, GLuint texId, GLfloat r, GLfloat g, GLfloat b);
};

#endif // OBJECT_SPAWNER_H
