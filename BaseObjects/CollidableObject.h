//
// Created by karl on 13.06.19.
//

#ifndef ASTEROID_COLLIDABLEOBJECT_H
#define ASTEROID_COLLIDABLEOBJECT_H

#include "KinematicObject.h"

class CollidableObject : public Object {
public:
    CollidableObject(std::string name, double radius) : Object(std::move(name)), radius(radius) {};

    bool collidesWith(const std::shared_ptr<CollidableObject>& other);

    const Eigen::Vector3d &getOrigin() const;

    double getRadius() const;

private:
    double radius;
    Eigen::Vector3d origin;
};


#endif //ASTEROID_COLLIDABLEOBJECT_H
