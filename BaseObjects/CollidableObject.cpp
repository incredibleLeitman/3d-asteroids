//
// Created by karl on 13.06.19.
//

#include "CollidableObject.h"

void CollidableObject::update(float delta) {
    Object::update(delta);

    origin = position;
}
