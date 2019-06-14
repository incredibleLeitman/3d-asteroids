//
// Created by karl on 14.06.19.
//

#ifndef ASTEROID_OBJECT_H
#define ASTEROID_OBJECT_H


#include <string>
#include <map>
#include <memory>

class Object {

public:
    Object(std::string name) : name(name) {};

    std::shared_ptr<Object> getParent();

    std::shared_ptr<Object> getChild(std::string name);

    void addChild(std::shared_ptr<Object> child);

private:
    std::map<std::string, std::shared_ptr<Object>> children;
    std::shared_ptr<Object> parent;
    std::string name;

};


#endif //ASTEROID_OBJECT_H
