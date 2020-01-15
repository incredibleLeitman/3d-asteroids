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
        : Object(std::move(name)), texId(texId), color{ r, g, b } {};

    /// Render the object via OpenGL, at the appropriate Transform of the Object
    virtual void render(const Eigen::Vector3d& playerPos) = 0;

protected:
    GLuint texId = 0;
    std::array<GLfloat, 3> color{ .0f, .0f, .0f };
};

/// Renders a sphere with any size and texture
class SphereRenderObject : public RenderObject {
public:
    SphereRenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius)
        : RenderObject(std::move(name), texId, r, g, b), radius(radius) {};

    void render(const Eigen::Vector3d& playerPos) override;

private:
    GLdouble radius;
};

/// Renders a cube with any size and texture
class CubeRenderObject : public RenderObject {
private:
    struct Vec3
    {
        float x;
        float y;
        float z;

        Vec3() : x(0), y(0), z(0) {};
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    };

    enum Side
    {
        top = 0,
        bottom = 1,
        front = 2,
        back = 3,
        left = 4,
        right = 5
    };

    Eigen::Vector3d SideToVector(Side side)
    {
        float half = dim / 2;
        switch (side)
        {
        case top:
            return Eigen::Vector3d(0, half, 0);
        case bottom:
            return Eigen::Vector3d(0, -half, 0);
        case front:
            return Eigen::Vector3d(0, 0, half);
        case back:
            return Eigen::Vector3d(0, 0, -half);
        case left:
            return Eigen::Vector3d(-half, 0, 0);
        case right:
            return Eigen::Vector3d(half, 0, 0);
        }
    }

public:
    CubeRenderObject(std::string name, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble dim)
        : RenderObject(std::move(name), texId, r, g, b), dim(dim)
    {
        float half = dim / 2;

        // top
        Side side = top;
        planes[side][0] = Vec3(-half, half, half);
        planes[side][1] = Vec3(half, half, half);
        planes[side][2] = Vec3(half, half, -half);
        planes[side][3] = Vec3(-half, half, -half);
        // bottom
        side = bottom;
        planes[side][0] = Vec3(-half, -half, -half);
        planes[side][1] = Vec3(half, -half, -half);
        planes[side][2] = Vec3(half, -half, half);
        planes[side][3] = Vec3(-half, -half, half);
        // front
        side = front;
        planes[side][0] = Vec3(-half, -half, half);
        planes[side][1] = Vec3(half, -half, half);
        planes[side][2] = Vec3(half, half, half);
        planes[side][3] = Vec3(-half, half, half);
        // back
        side = back;
        planes[side][0] = Vec3(half, -half, -half);
        planes[side][1] = Vec3(-half, -half, -half);
        planes[side][2] = Vec3(-half, half, -half);
        planes[side][3] = Vec3(half, half, -half);
        // left
        side = left;
        planes[side][0] = Vec3(-half, -half, -half);
        planes[side][1] = Vec3(-half, -half, half);
        planes[side][2] = Vec3(-half, half, half);
        planes[side][3] = Vec3(-half, half, -half);
        // right
        side = right;
        planes[side][0] = Vec3(half, -half, half);
        planes[side][1] = Vec3(half, -half, -half);
        planes[side][2] = Vec3(half, half, -half);
        planes[side][3] = Vec3(half, half, half);
    };

    void render(const Eigen::Vector3d& playerPos) override;

private:
    GLdouble dim;
    std::map<Side, Vec3[4] > planes;
};

/// Renders a spaceship cockpit, e.g. for putting the player camera inside
class CockpitRenderObject : public RenderObject {
public:
    CockpitRenderObject(std::string name, GLuint texId, float extentX, float extentY, float distZ, float topOffset, float topDistance)
        : RenderObject(std::move(name), texId, 1.0, 1.0, 1.0), extentX(extentX), extentY(extentY), distZ(distZ), topOffset(topOffset), topDistance(topDistance) {};

    void render(const Eigen::Vector3d& playerPos) override;

private:
    float extentX;
    float extentY;
    float distZ;
    float topOffset;
    float topDistance;
};

/// Renders a given modell
class ModelRenderObject : public RenderObject {
public:
    ModelRenderObject(std::string name, int modelId, GLuint texId)
        : RenderObject(std::move(name), texId, 1.0, 1.0, 1.0), modelId(modelId) {};

    void render(const Eigen::Vector3d& playerPos) override;

private:
    int modelId;
};

#endif //RENDER_OBJECT_H
