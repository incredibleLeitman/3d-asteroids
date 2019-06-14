//
// Created by karl on 14.06.19.
//

#include "Object.h"

std::shared_ptr<Object> Object::getParent() {
    return parent;
}

std::shared_ptr<Object> Object::getChild(std::string name) {
    return children[name];
}

void Object::addChild(std::shared_ptr<Object> child) {
    children[child->name] = child;

    child->parent = std::shared_ptr<Object>(this);
}
