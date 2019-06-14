#pragma once
#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

class RenderObject : public Object {
public:
    RenderObject(std::string name) : Object(name) {};

    void render();
};

#endif //RENDER_OBJECT_H
