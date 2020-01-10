#include <iostream>

#include "RenderObject.h"
#include "../Util/TextureManager.h"

const int DEFAULT_SPHERE_SLICES = 5;
const int DEFAULT_SPHERE_STACKS = 8;

bool setIfDiff(GLboolean val, GLenum cap) {
    if (val != glIsEnabled(cap)) {
        if (val == GL_TRUE) {
            glEnable(cap);
        }
        else {
            glDisable(cap);
        }
        return true;
    }
    return false;
}

void SphereRenderObject::render(float distance) {
    if (this->getParent() == nullptr) {
        throw std::exception();
    }

    GLboolean enableTexture = glIsEnabled(GL_TEXTURE_2D);
    GLboolean enableLighting = glIsEnabled(GL_LIGHTING);
    glPushMatrix();
    try {
        if (texId != 0) {
            if (enableTexture != GL_TRUE) glEnable(GL_TEXTURE_2D);
            TextureManager::Inst()->bindTexture(texId);
        }

        // TODO: reset color?
        if (color[0] != 0 || color[1] != 0 || color[2] != 0) {
            if (enableLighting == GL_TRUE) glDisable(GL_LIGHTING);
            glColor3f(color[0], color[1], color[2]);
        }

        // Transform by the object's Transform matrix
        float matrix[16];
        Eigen::Matrix4d transform = getTransform();

        for (int i = 0; i < 16; i++) {
            matrix[i] = transform(i);
        }

        glMultMatrixf(matrix);

        int slices = DEFAULT_SPHERE_SLICES;
        int stacks = DEFAULT_SPHERE_STACKS;
        if (distance < 100)
        {
            slices = 15;
            stacks = 20;
        }

        if (texId != 0) {
            // There is a texture -> draw a gluSphere with a quadric texture
            GLUquadric* sphere = gluNewQuadric();
            gluQuadricTexture(sphere, GL_TRUE);
            //  0.1     15      15
            //  0.3     36      72
            //  1000    500     500
            gluSphere(sphere, radius, slices, stacks);
        }
        else {
            // No texture -> draw a default solid sphere
            glutSolidSphere(radius, slices, stacks);
        }
    }
    catch (std::exception & e)
    {
        throw e;
    }
    glPopMatrix();

    // reset all set configurations
    setIfDiff(enableLighting, GL_LIGHTING);
    setIfDiff(enableTexture, GL_TEXTURE_2D);
}

void CubeRenderObject::render(float distance) {
    if (this->getParent() == nullptr) {
        throw std::exception();
    }

    GLboolean enableTexture = glIsEnabled(GL_TEXTURE_2D);
    GLboolean enableLighting = glIsEnabled(GL_LIGHTING);
    glPushMatrix();
    try {
        if (texId != 0) {
            if (enableTexture != GL_TRUE) glEnable(GL_TEXTURE_2D);
            TextureManager::Inst()->bindTexture(texId);
        }

        // TODO: reset color?
        if (color[0] != 0 || color[1] != 0 || color[2] != 0) {
            if (enableLighting == GL_TRUE) glDisable(GL_LIGHTING);
            glColor3f(color[0], color[1], color[2]);
        }

        // Transform by the object's Transform matrix
        float matrix[16];
        Eigen::Matrix4d transform = getTransform();

        for (int i = 0; i < 16; i++) {
            matrix[i] = transform(i);
        }

        glMultMatrixf(matrix);
        glBegin(GL_QUADS);

        // Top
        float half = dim / 2;
        glTexCoord2f(0, 0);
        glVertex3f(-half, half, -half);
        glTexCoord2f(1, 0);
        glVertex3f(half, half, -half);
        glTexCoord2f(1, 1);
        glVertex3f(half, half, half);
        glTexCoord2f(0, 1);
        glVertex3f(-half, half, half);

        // Bottom
        glTexCoord2f(0, 0);
        glVertex3f(-half, -half, -half);
        glTexCoord2f(1, 0);
        glVertex3f(half, -half, -half);
        glTexCoord2f(1, 1);
        glVertex3f(half, -half, half);
        glTexCoord2f(0, 1);
        glVertex3f(-half, -half, half);

        // Back
        glTexCoord2f(0, 0);
        glVertex3f(-half, -half, -half);
        glTexCoord2f(1, 0);
        glVertex3f(half, -half, -half);
        glTexCoord2f(1, 1);
        glVertex3f(half, half, -half);
        glTexCoord2f(0, 1);
        glVertex3f(-half, half, -half);

        // Front
        glTexCoord2f(0, 0);
        glVertex3f(-half, -half, half);
        glTexCoord2f(1, 0);
        glVertex3f(half, -half, half);
        glTexCoord2f(1, 1);
        glVertex3f(half, half, half);
        glTexCoord2f(0, 1);
        glVertex3f(-half, half, half);

        // Left
        glTexCoord2f(0, 0);
        glVertex3f(-half, half, -half);
        glTexCoord2f(1, 0);
        glVertex3f(-half, half, half);
        glTexCoord2f(1, 1);
        glVertex3f(-half, -half, half);
        glTexCoord2f(0, 1);
        glVertex3f(-half, -half, -half);

        // Right
        glTexCoord2f(0, 0);
        glVertex3f(half, half, -half);
        glTexCoord2f(1, 0);
        glVertex3f(half, half, half);
        glTexCoord2f(1, 1);
        glVertex3f(half, -half, half);
        glTexCoord2f(0, 1);
        glVertex3f(half, -half, -half);

        glEnd();
    }
    catch (std::exception & e)
    {
        throw e;
    }
    glPopMatrix();

    // reset all set configurations
    setIfDiff(enableLighting, GL_LIGHTING);
    setIfDiff(enableTexture, GL_TEXTURE_2D);
}

void CockpitRenderObject::render(float distance) {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    TextureManager::Inst()->bindTexture(texId);

    // Transform by the object's Transform matrix
    float matrix[16];
    Eigen::Matrix4d transform = getTransform();

    for (int i = 0; i < 16; i++) {
        matrix[i] = transform(i);
    }

    glMultMatrixf(matrix);

    glTranslatef(0.0, -1.7, 0.0);

    glBegin(GL_QUADS);

    // Top
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, topDistance, -extentX);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, topDistance, -extentX);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, topDistance, extentX);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, topDistance, extentX);

    // Back
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, extentX);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, extentX);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, topDistance, extentX);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, topDistance, extentX);

    // Bottom
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, distZ);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, -extentY, extentX);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, -extentY, extentX);

    // Left
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, extentX);
    glTexCoord2f(1, 0);
    glVertex3f(-extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(-extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, extentY, extentX);

    // Front
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, distZ);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, extentY, distZ - topOffset);

    // Right
    glTexCoord2f(0, 0);
    glVertex3f(extentX, -extentY, extentX);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(extentX, extentY, extentX);

    glEnd();

    glPopMatrix();
}