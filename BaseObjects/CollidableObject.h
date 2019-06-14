//
// Created by karl on 13.06.19.
//

#ifndef ASTEROID_COLLIDABLEOBJECT_H
#define ASTEROID_COLLIDABLEOBJECT_H


#include "Object.h"
#include "Collidable.h"

class CollidableObject : public Object, public Collidable {
public:
    CollidableObject(Eigen::Vector3d angularAccel, Eigen::Vector3d linearAccel, double radius) : Object(angularAccel,
                                                                                                        linearAccel),
                                                                                                 Collidable(radius) {};

    void update(float delta) override;
};


#endif //ASTEROID_COLLIDABLEOBJECT_H
