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

void SphereRenderObject::render(float step) {
    if (this->getParent() == nullptr)
    {
        throw std::exception("cannot render object without parent!");
    }

    GLboolean enableTexture = glIsEnabled(GL_TEXTURE_2D);
    GLboolean enableLighting = glIsEnabled(GL_LIGHTING);
    glPushMatrix();
    try
    {
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

        Eigen::Vector3d pos = this->getParent()->getTransform().col(3).head<3>();
        glTranslatef(pos.x(), pos.y(), pos.z());

        glPushMatrix();

        // rotate
        if (rotspeed != 0)
        {
            if (rot_x == 0.0f && rot_y == 0.0f && rot_z == 0.0f)
            {
                // lol
            }
            else
            {
                // step is between 0 and 23
                glRotatef(step * rotspeed, rot_x, rot_y, rot_z);
            }
        }

        if (texId != 0)
        {
            GLUquadric *sphere = gluNewQuadric();
            gluQuadricTexture(sphere, GL_TRUE);
            //  0.1     15      15
            //  0.3     36      72
            //  1000    500     500
            gluSphere(sphere, radius, 36, 72);
        }
        else
        {
            glutSolidSphere(radius, 15, 15);
        }
    }
    catch (std::exception &e)
    {
        throw e;
    }
    //finally // so sad ;(
    {
        glPopMatrix();
        glPopMatrix();

        // reset all set configurations
        setIfDiff(enableTexture, GL_TEXTURE_2D);
        setIfDiff(enableLighting, GL_LIGHTING);
    }
}