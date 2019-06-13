//
// Created by karl on 01.06.19.
//

#ifndef ASTEROID_SHIP_H
#define ASTEROID_SHIP_H

#include <vector>
#include "Eigen/Geometry"


class Ship {

public:
    Ship(Eigen::Vector3d angularAccel, Eigen::Vector3d linearAccel);

    void update(float delta);

    Eigen::Vector3d angularVelocity;
    Eigen::Vector3d angularAccel;
    Eigen::Vector3d linearVelocity;
    Eigen::Vector3d linearAccel;
    Eigen::Vector3d position;
    Eigen::Vector3d angularThrust;
    Eigen::Vector3d linearThrust;

    Eigen::Matrix3d basis = Eigen::Matrix3d::Identity();
};


#endif //ASTEROID_SHIP_H
