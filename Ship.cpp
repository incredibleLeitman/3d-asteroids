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
    // Forward movement fixed by angles
    getLinearVelocity()[0] += getLinearAccel()[0] * getLinearThrust()[2] * delta * sin(getAngle()[1] * (M_PI / 180)) * cos(getAngle()[0] * (M_PI / 180));
    getLinearVelocity()[1] += getLinearAccel()[1] * getLinearThrust()[2] * delta * -sin(getAngle()[0] * (M_PI / 180));
    getLinearVelocity()[2] += getLinearAccel()[2] * getLinearThrust()[2] * delta * cos(getAngle()[1] * (M_PI / 180)) * cos(getAngle()[0] * (M_PI / 180));

    for (int dim = 0; dim < 3; dim++) {
        // TODO: This doesn't work: Once the X rotation has been changed, the Z rotation isn't as expected
        getAngularVelocity()[dim] += getAngularAccel()[dim] * getAngularThrust()[dim] * delta;

        position[dim] += getLinearVelocity()[dim] * delta;
        angle[dim] += getAngularVelocity()[dim] * delta;
    }
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
