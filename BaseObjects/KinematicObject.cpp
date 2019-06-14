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

    // Rotate our basis depending on how much we're rotating this frame
    Eigen::AngleAxisd rollAngle(angularVelocity[2] * (M_PI / 180) * delta, basis.col(2));
    Eigen::AngleAxisd yawAngle(angularVelocity[1] * (M_PI / 180) * delta, basis.col(1));
    Eigen::AngleAxisd pitchAngle(angularVelocity[0] * (M_PI / 180) * delta, basis.col(0));

    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;
    basis = q.matrix() * basis;

    // Add this frame's velocity to our global linear velocity, relative to our angle
    linearVelocity += basis * addedLinearVelocity * delta;

    transform.col(3).head<3>() += linearVelocity;

    // Update the Object's Transform
    transform.col(0).head<3>() = basis.col(0);
    transform.col(1).head<3>() = basis.col(1);
    transform.col(2).head<3>() = basis.col(2);
}