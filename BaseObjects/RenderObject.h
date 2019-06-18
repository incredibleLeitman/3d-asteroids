#pragma once
#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Object.h"

class RenderObject : public Object {
public:
    RenderObject(std::string name) : Object(name) {};

    void render();
};

#endif //RENDER_OBJECT_H
