//
// Created by karl on 13.06.19.
//

#include "CollidableObject.h"

bool CollidableObject::collidesWith(CollidableObject other) {
    // Return true if the objects are closer to each other than their added radii
    return (origin - other.origin).squaredNorm() < radius + other.radius;
}
