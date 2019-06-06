//
// Created by karl on 01.06.19.
//

#ifndef ASTEROID_SHIP_H
#define ASTEROID_SHIP_H

#include <vector>
#include "Eigen/Geometry"


class Ship {

public:
    Ship(std::vector<float> angularAccel, std::vector<float> linearAccel);

    std::vector<float> &getAngularVelocity();

    std::vector<float> &getAngularAccel();

    std::vector<float> &getLinearVelocity();

    std::vector<float> &getLinearAccel();

    const std::vector<float> &getPosition() const;

    const std::vector<float> &getAngle() const;

    void update(float delta);

    std::vector<float> &getAngularThrust();

    std::vector<float> &getLinearThrust();

public:
    std::vector<float> angularVelocity = std::vector<float>(3);
    std::vector<float> angularAccel = std::vector<float>(3);
    std::vector<float> linearVelocity = std::vector<float>(3);
    std::vector<float> linearAccel = std::vector<float>(3);
    std::vector<float> position = std::vector<float>(3);
    std::vector<float> angle = std::vector<float>(3);
    std::vector<float> angularThrust = std::vector<float>(3);
    std::vector<float> linearThrust = std::vector<float>(3);

    Eigen::Matrix3d basis = Eigen::Matrix3d::Identity();
    Eigen::Vector3d velocity;
};


#endif //ASTEROID_SHIP_H
