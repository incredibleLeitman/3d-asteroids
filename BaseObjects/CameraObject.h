//
// Created by karl on 14.06.19.
//
#ifndef ASTEROID_CAMERAOBJECT_H
#define ASTEROID_CAMERAOBJECT_H

#include "Object.h"

/// A camera (which e.g. the player has)
class CameraObject : public Object {
public:
    explicit CameraObject(std::string name) : Object(std::move(name)) {};

    /// Set the camera by multiplying with the inverse transform
    void setCamera();
};

#endif //ASTEROID_CAMERAOBJECT_H
