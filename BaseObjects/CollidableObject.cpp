//
// Created by karl on 13.06.19.
//

#include <memory>
#include <iostream>
#include "CollidableObject.h"

bool CollidableObject::collidesWith(const std::shared_ptr<CollidableObject>& other) {
    return (getOrigin() - other->getOrigin()).squaredNorm() < (getRadius() + other->getRadius()) * (getRadius() + other->getRadius());
}

Eigen::Vector3d CollidableObject::getOrigin() {
    return getTransform().col(3).head<3>();
}

double CollidableObject::getRadius() const {
    return radius;
}
