#include <utility>

#pragma once
#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <GL/glut.h>

#include "Object.h"

/// Abstract class for objects which can be rendered in the OpenGL draw function
class RenderObject : public Object {
public:
    RenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b)
            : Object(std::move(name)), texId(texId), color{r, g, b} {};

    /// Render the object via OpenGL, at the appropriate Transform of the Object
    virtual void render() = 0;

protected:
    GLuint texId = 0;
    std::array<GLfloat, 3> color{.0f, .0f, .0f};
};


/// Renders a sphere with any size and texture
class SphereRenderObject : public RenderObject {
public:
    SphereRenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius)
            : RenderObject(std::move(name), texId, r, g, b), radius(radius) {};

    void render() override;

private:
    GLdouble radius;
};

#endif //RENDER_OBJECT_H
