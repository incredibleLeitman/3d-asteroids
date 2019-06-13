//
// Created by karl on 13.06.19.
//

#include "Collidable.h"

bool Collidable::collidesWith(Collidable other) {
    // Return true if the objects are closer to each other than their added radii
    return (origin - other.origin).squaredNorm() < radius + other.radius;
}
