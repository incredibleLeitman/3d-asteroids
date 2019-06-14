//
// Created by karl on 14.06.19.
//

#ifndef ASTEROID_OBJECT_H
#define ASTEROID_OBJECT_H


#include <string>
#include <map>
#include <memory>
#include "../Eigen/Geometry"

class Object {

public:
    Object(std::string name) : name(name) {};

    Object(std::string name, Eigen::Vector3d startPosition) : name(name) {
        transform.col(3).head<3>() = startPosition;
    };

    std::shared_ptr<Object> getParent();

    std::shared_ptr<Object> getChild(std::string name);

    void addChild(std::shared_ptr<Object> child);

    Eigen::Matrix4d getTransform();

protected:
    std::map<std::string, std::shared_ptr<Object>> children;
    std::shared_ptr<Object> parent;
    std::string name;
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
};


#endif //ASTEROID_OBJECT_H
