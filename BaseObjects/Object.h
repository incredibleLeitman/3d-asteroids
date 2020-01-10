//
// Created by karl on 14.06.19.
//

#ifndef ASTEROID_OBJECT_H
#define ASTEROID_OBJECT_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../Eigen/Geometry"

/// The base Object class - on its own, it has just a Transform matrix and a name.
/// It can have other Objects or any class derived from Object as children, thus
///  allowing to compose more complex objects in a tree structure.
class Object {
public:
    explicit Object(std::string name) : name(std::move(name)) {};

    /// Give the Object a start position
    Object(std::string name, const Eigen::Vector3d& startPosition) : name(std::move(name)) {
        transform.col(3).head<3>() = startPosition;
    };

    virtual ~Object() = default;

    /// Get the Object which has this one as a child
    std::shared_ptr<Object> getParent();

    /// Get a specific child of this Object by its name
    std::shared_ptr<Object> getChild(const std::string& child_name);

    /// Get all children of this Object
    std::vector<std::shared_ptr<Object>> getChildren();

    /// Add a child Object to this one
    void addChild(const std::shared_ptr<Object>& child);

    /// remove child
    void removeChild(const std::string& child_name);

    /// Get the global 4x4 Transform matrix for this Object - e.g. for multiplying in OpenGL
    /// Uses the Transforms of all parent Objects to get the absolute global matrix in world space
    Eigen::Matrix4d getTransform();

    std::string getName();

protected:
    std::map<std::string, std::shared_ptr<Object>> children;
    std::shared_ptr<Object> parent;
    std::string name;
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
};

#endif //ASTEROID_OBJECT_H
