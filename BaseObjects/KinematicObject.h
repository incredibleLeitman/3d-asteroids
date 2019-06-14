#include <utility>

#include <utility>

#include <utility>

//
// Created by karl on 01.06.19.
//

#ifndef ASTEROID_KINEMATICOBJECT_H
#define ASTEROID_KINEMATICOBJECT_H

#include <vector>
#include "../Eigen/Geometry"
#include "Object.h"


class KinematicObject : public Object {

public:
    KinematicObject(std::string name, Eigen::Vector3d startPos, Eigen::Vector3d angularAccel,
                    Eigen::Vector3d linearAccel) : Object(std::move(name), std::move(startPos)),
                                                   angularAccel(std::move(
                                                           angularAccel)),
                                                   linearAccel(std::move(
                                                           linearAccel)) {};

    virtual void update(float delta);

    Eigen::Vector3d angularThrust;
    Eigen::Vector3d linearThrust;

    Eigen::Vector3d angularVelocity;
    Eigen::Vector3d linearVelocity;

private:
    Eigen::Vector3d angularAccel;
    Eigen::Vector3d linearAccel;

    Eigen::Matrix3d localRotationMatrix = Eigen::Matrix3d::Identity();
};


#endif //ASTEROID_KINEMATICOBJECT_H
