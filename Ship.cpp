#include <utility>

#include <cmath>
#include <iostream>

//
// Created by karl on 01.06.19.
//

#include "Ship.h"

std::vector<float> &Ship::getAngularVelocity() {
    return angularVelocity;
}

std::vector<float> &Ship::getAngularAccel() {
    return angularAccel;
}

std::vector<float> &Ship::getLinearVelocity() {
    return linearVelocity;
}

std::vector<float> &Ship::getLinearAccel() {
    return linearAccel;
}

const std::vector<float> &Ship::getPosition() const {
    return position;
}

const std::vector<float> &Ship::getAngle() const {
    return angle;
}

void Ship::update(float delta) {
    Eigen::Vector3d newVel;
    Eigen::Vector3d newAng;

    // Update velocities
    for (int dim = 0; dim < 3; dim++) {
        getAngularVelocity()[dim] += getAngularAccel()[dim] * getAngularThrust()[dim] * delta;
        newVel[dim] = getLinearAccel()[dim] * getLinearThrust()[dim] * delta;
    }

    // Rotate our basis depending on how much we're rotating this frame
    Eigen::AngleAxisd rollAngle(getAngularVelocity()[2] * (M_PI / 180) * delta, basis.col(2));
    Eigen::AngleAxisd yawAngle(getAngularVelocity()[1] * (M_PI / 180) * delta, basis.col(1));
    Eigen::AngleAxisd pitchAngle(getAngularVelocity()[0] * (M_PI / 180) * delta, basis.col(0));

    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

    basis = q.matrix() * basis;

    std::cout << basis << std::endl << std::endl;

    // Apply rotation to our angle Vector (Euler angles)
    Eigen::Vector3d eulerAngles = basis.eulerAngles(0, 1, 2);
    angle[0] = eulerAngles[0];
    angle[1] = eulerAngles[1];
    angle[2] = eulerAngles[2];

    // Apply linear velocity relative to our angle
    Eigen::Vector3d pos = Eigen::Vector3d(getPosition()[0], getPosition()[1], getPosition()[2]);
    velocity += basis * newVel * delta;
    pos += velocity;

    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
}

Ship::Ship(std::vector<float> angularAccel, std::vector<float> linearAccel) : angularAccel(std::move(angularAccel)),
                                                                              linearAccel(std::move(linearAccel)) {
    position[2] = 8; // TODO: Move start position
}

std::vector<float> &Ship::getAngularThrust() {
    return angularThrust;
}

std::vector<float> &Ship::getLinearThrust() {
    return linearThrust;
}
