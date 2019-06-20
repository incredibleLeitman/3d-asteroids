#include <iostream>

#include "RenderObject.h"
#include "../Util/TextureManager.h"

bool setIfDiff(GLboolean val, GLenum cap) {
    if (val != glIsEnabled(cap)) {
        if (val == GL_TRUE) {
            glEnable(cap);
        } else {
            glDisable(cap);
        }
        return true;
    }
    return false;
}

void SphereRenderObject::render() {
    if (this->getParent() == nullptr) {
        throw std::exception();
    }

    GLboolean enableTexture = glIsEnabled(GL_TEXTURE_2D);
    glPushMatrix();
    try {
        if (texId != 0) {
            if (enableTexture != GL_TRUE) glEnable(GL_TEXTURE_2D);
            TextureManager::Inst()->bindTexture(texId);
        }

        // TODO: reset color?
        if (color[0] != 0 || color[1] != 0 || color[2] != 0) {
            glColor3f(color[0], color[1], color[2]);
        }

        // Transform by the object's Transform matrix
        float matrix[16];
        Eigen::Matrix4d transform = getTransform();

        for (int i = 0; i < 16; i++) {
            matrix[i] = transform(i);
        }

        glMultMatrixf(matrix);

        if (texId != 0) {
            GLUquadric *sphere = gluNewQuadric();
            gluQuadricTexture(sphere, GL_TRUE);
            //  0.1     15      15
            //  0.3     36      72
            //  1000    500     500
            gluSphere(sphere, radius, 36, 72);
        } else {
            glutSolidSphere(radius, 15, 15);
        }
    }
    catch (std::exception &e) {
        throw e;
    }
    glPopMatrix();

    // reset all set configurations
    setIfDiff(enableTexture, GL_TEXTURE_2D);
}

void CockpitRenderObject::render() {
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
