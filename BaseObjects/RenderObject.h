#include <utility>

#pragma once
#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <GL/glut.h>

#include "Object.h"

class RenderObject : public Object {
public:
    RenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b)
        : Object(std::move(name)), texId(texId), color{r, g, b} {};

    virtual void render() = 0;

protected:
    GLuint texId = 0;
    std::array<GLfloat, 3> color{ 0, 0, 0 };
};

class SphereRenderObject : public RenderObject {
public:
    SphereRenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius)
        : RenderObject(name, texId, r, g, b), radius(radius) {};

    void render();

private:
    GLdouble radius;
};

#endif //RENDER_OBJECT_H
