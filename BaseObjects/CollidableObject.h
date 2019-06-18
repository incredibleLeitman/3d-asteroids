//
// Created by karl on 13.06.19.
//

#ifndef ASTEROID_COLLIDABLEOBJECT_H
#define ASTEROID_COLLIDABLEOBJECT_H


#include "KinematicObject.h"

class CollidableObject : public Object {
public:
    CollidableObject(std::string name, double radius) : Object(name), radius(radius) {};

    bool collidesWith(CollidableObject other);

private:
    Eigen::Vector3d origin;
    double radius;
};


#endif //ASTEROID_COLLIDABLEOBJECT_H
