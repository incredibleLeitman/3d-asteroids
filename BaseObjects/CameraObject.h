#include <utility>

//
// Created by karl on 14.06.19.
//

#ifndef ASTEROID_CAMERAOBJECT_H
#define ASTEROID_CAMERAOBJECT_H


#include "Object.h"

class CameraObject : public Object {
public:
    explicit CameraObject(std::string name) : Object(std::move(name)) {};

    void setCamera();
};


#endif //ASTEROID_CAMERAOBJECT_H
