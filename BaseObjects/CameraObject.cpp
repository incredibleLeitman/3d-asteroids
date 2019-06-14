//
// Created by karl on 14.06.19.
//

#include <GL/gl.h>
#include <iostream>
#include "CameraObject.h"

void CameraObject::setCamera() {
    // Turn our transform into a 4x4 array since that's the format OpenGL needs
    float matrix[16];
    Eigen::Matrix4d inverseTransform = getTransform().inverse();

    for (int i = 0; i < 16; i++) {
        matrix[i] = inverseTransform(i);
    }

    glMultMatrixf(matrix);
}
