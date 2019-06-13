//
// Created by karl on 13.06.19.
//

#ifndef ASTEROID_COLLIDABLE_H
#define ASTEROID_COLLIDABLE_H


#include "Eigen/Geometry"

class Collidable {
public:
    Collidable(double _radius) : radius(_radius), origin(Eigen::Vector3d{0.0, 0.0, 0.0}) {};

    bool collidesWith(Collidable other);

    Eigen::Vector3d origin;
    double radius;
};


#endif //ASTEROID_COLLIDABLE_H
