#pragma once
#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <GL/glut.h>

#include "Object.h"

class RenderObject : public Object {
public:
    RenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b)
            : Object(std::move(name)), texId(texId), color{r, g, b} {};

    virtual void render(float step) = 0;

protected:
    GLuint texId = 0;
    std::array<GLfloat, 3> color{.0f, .0f, .0f};
};

class SphereRenderObject : public RenderObject {
public:
    SphereRenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius, float rotspeed,
                       float rot_x, float rot_y, float rot_z)
            : RenderObject(name, texId, r, g, b), radius(radius), rotspeed(rotspeed), rot_x(rot_x), rot_y(rot_y),
              rot_z(rot_z) {};

    void render(float step);

private:
    GLdouble radius;
    float rotspeed = 0.0f;
    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float rot_z = 0.0f;
};

#endif //RENDER_OBJECT_H
