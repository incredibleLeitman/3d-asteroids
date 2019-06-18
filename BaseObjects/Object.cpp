//
// Created by karl on 14.06.19.
//

#include "Object.h"

std::shared_ptr<Object> Object::getParent() {
    return parent;
}

std::shared_ptr<Object> Object::getChild(const std::string &child_name) {
    return children[child_name];
}

std::vector<std::shared_ptr<Object>> Object::getChildren() {
    std::vector<std::shared_ptr<Object>> v_children = std::vector<std::shared_ptr<Object>>();
    std::transform(children.begin(), children.end(), std::back_inserter(v_children),
                   [](const std::map<std::string, std::shared_ptr<Object>>::value_type &val) { return val.second; });
    return v_children;
}

void Object::addChild(const std::shared_ptr<Object> &child) {
    children[child->name] = child;

    child->parent = std::shared_ptr<Object>(this);
}

Eigen::Matrix4d Object::getTransform() {
    if (getParent() == nullptr) {
        return transform;
    } else {
        return transform * getParent()->getTransform();
    }
}

std::string Object::getName() {
    return name;
}