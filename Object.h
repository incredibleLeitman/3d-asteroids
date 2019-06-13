//
// Created by karl on 01.06.19.
//

#ifndef ASTEROID_OBJECT_H
#define ASTEROID_OBJECT_H

#include <vector>
#include "Eigen/Geometry"


class Object {

public:
    Object(Eigen::Vector3d angularAccel, Eigen::Vector3d linearAccel);

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


#endif //ASTEROID_OBJECT_H
