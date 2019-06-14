//
// Created by karl on 01.06.19.
//

#define _USE_MATH_DEFINES

#include <cmath>
#include <utility>
#include <iostream>

#include "../Defines.h"
#include "KinematicObject.h"

void KinematicObject::update(float delta) {
    // Add acceleration depending on where there is thrust
    angularVelocity += angularAccel.cwiseProduct(angularThrust) * delta;
    Eigen::Vector3d addedLinearVelocity = linearAccel.cwiseProduct(linearThrust) * delta;

    // Add this frame's rotation to our local rotation matrix
    Eigen::AngleAxisd rollAngle(angularVelocity[2] * (M_PI / 180) * delta, localRotationMatrix.col(2));
    Eigen::AngleAxisd yawAngle(angularVelocity[1] * (M_PI / 180) * delta, localRotationMatrix.col(1));
    Eigen::AngleAxisd pitchAngle(angularVelocity[0] * (M_PI / 180) * delta, localRotationMatrix.col(0));

    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;
    localRotationMatrix = q.matrix() * localRotationMatrix;

    // Add this frame's velocity to our global linear velocity, relative to our angle
    linearVelocity += localRotationMatrix * addedLinearVelocity * delta;

    // Update the Object's Transform
    transform.col(0).head<3>() = localRotationMatrix.col(0);
    transform.col(1).head<3>() = localRotationMatrix.col(1);
    transform.col(2).head<3>() = localRotationMatrix.col(2);
    transform.col(3).head<3>() += linearVelocity; // Translation column
}