//
// Created by karl on 13.06.19.
//

#include <memory>
#include "CollidableObject.h"

bool CollidableObject::collidesWith(const std::shared_ptr<CollidableObject>& other) {
    // Return true if the objects are closer to each other than their added radii
    return (origin - other->getOrigin()).squaredNorm() < radius + other->getRadius();
}

const Eigen::Vector3d &CollidableObject::getOrigin() const {
    return origin;
}

double CollidableObject::getRadius() const {
    return radius;
}
