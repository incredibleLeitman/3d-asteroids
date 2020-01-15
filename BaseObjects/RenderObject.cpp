#include <iostream>

#include "RenderObject.h"
#include "../Util/TextureManager.h"
#include "../Util/ModelManager.h"

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

void SphereRenderObject::render(const Eigen::Vector3d& playerPos) {
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

        float distance = (playerPos - transform.col(3).head<3>()).norm();
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

void CubeRenderObject::render(const Eigen::Vector3d& playerPos) {
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

        // sort transparent objects
        std::map<float, Vec3[4]> sorted;
        for (auto& object : planes) {
            Eigen::Vector3d side = SideToVector(object.first) + transform.col(3).head<3>();
            float distance = (side - playerPos).norm();
            sorted[distance][0] = object.second[0];
            sorted[distance][1] = object.second[1];
            sorted[distance][2] = object.second[2];
            sorted[distance][3] = object.second[3];
            //fprintf(stderr, "side %d has distance %f\n", object.first, distance);
        }

        // render all transparent objects
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);
        for (std::map<float, Vec3[4]>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            //fprintf(stderr, "drawing distance %f\n", it->first);
            glTexCoord2f(0, 0);
            glVertex3f(it->second[0].x, it->second[0].y, it->second[0].z);
            glTexCoord2f(1, 0);
            glVertex3f(it->second[1].x, it->second[1].y, it->second[1].z);
            glTexCoord2f(1, 1);
            glVertex3f(it->second[2].x, it->second[2].y, it->second[2].z);
            glTexCoord2f(0, 1);
            glVertex3f(it->second[3].x, it->second[3].y, it->second[3].z);
        }
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

//void CockpitRenderObject::render(float distance) {
void CockpitRenderObject::render(const Eigen::Vector3d&) {
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

void ModelRenderObject::render(const Eigen::Vector3d& playerPos) {
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

        int lodModel = modelId;
        float distance = (playerPos - transform.col(3).head<3>()).norm();
        if (distance > 10)
        {
            lodModel++;
        }
        if (distance > 50)
        {
            lodModel++;
        }
        Mesh mesh = ModelManager::Inst()->getModel(lodModel);

        glBegin(GL_TRIANGLES);
        for (auto& vertex : mesh.Vertices)
        {
            glTexCoord2f(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y);
            glVertex3f(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
        }
        glEnd();
    }
    catch (std::exception & e)
    {
        fprintf(stderr, "error in ModelRenderObject %s: %s\n", name.c_str(), e.what());
        throw e;
    }
    glPopMatrix();

    // reset all set configurations
    setIfDiff(enableLighting, GL_LIGHTING);
    setIfDiff(enableTexture, GL_TEXTURE_2D);
}