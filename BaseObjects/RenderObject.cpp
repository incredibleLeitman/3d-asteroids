#include <iostream>

#include "RenderObject.h"
#include "..\Util\TextureManager.h"

bool setIfDiff(GLboolean val, GLenum cap)
{
    if (val != glIsEnabled(cap))
    {
        if (val == GL_TRUE)
        {
            glEnable(cap);
        }
        else
        {
            glDisable(cap);
        }
        return true;
    }
    return false;
}

void SphereRenderObject::render() {
    if (this->getParent() == nullptr)
    {
        throw std::exception("cannot render object without parent!");
    }

    GLboolean enableTexture = glIsEnabled(GL_TEXTURE_2D);
    GLboolean enableLighting = glIsEnabled(GL_LIGHTING);
    if (texId != 0)
    {
        if (enableTexture != GL_TRUE) glEnable(GL_TEXTURE_2D);
        TextureManager::Inst()->bindTexture(texId);
    }

    // TODO: reset color?
    if (color[0] != 0 || color[1] != 0 || color[2] != 0)
    {
        glColor3f(color[0], color[1], color[2]);
    }

    glPushMatrix();
    Eigen::Vector3d pos = this->getParent()->getTransform().col(3).head<3>();
    glTranslatef(pos.x(), pos.y(), pos.z());
    if (texId != 0)
    {
        GLUquadric *sphere = gluNewQuadric();
        gluQuadricTexture(sphere, GL_TRUE);
        //gluSphere(sphere, radius, 36, 72);
        //  0.1     15      15
        //  0.3     36      72
        //  1000    500     500
        gluSphere(sphere, radius, radius*100, radius * 100);
    }
    else
    {
        //glutSolidSphere(radius, 15, 15);
        glutSolidSphere(radius, radius * 100, radius * 100);
    }
    glPopMatrix();

    // reset all set configurations
    setIfDiff(enableTexture, GL_TEXTURE_2D);
    setIfDiff(enableLighting, GL_LIGHTING);
}