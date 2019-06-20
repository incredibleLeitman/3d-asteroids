//
// Created by karl on 13.06.19.
//

#ifndef ASTEROID_COLLIDABLEOBJECT_H
#define ASTEROID_COLLIDABLEOBJECT_H

#include "KinematicObject.h"

/// A spherical collider which can collide with other CollidableObjects
class CollidableObject : public Object {
public:
    CollidableObject(std::string name, double radius) : Object(std::move(name)), radius(radius) {};

    /// Returns true if the objects are closer to each other than their added radii (-> They collide)
    bool collidesWith(const std::shared_ptr<CollidableObject>& other);

    Eigen::Vector3d getOrigin();

    double getRadius() const;

private:
    double radius;
    Eigen::Vector3d origin;
};


#endif //ASTEROID_COLLIDABLEOBJECT_H
