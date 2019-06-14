#pragma once
#ifndef OBJECT_SPAWNER_H
#define OBJECT_SPAWNER_H

class ObjectSpawner {
public:
    ObjectSpawner() = default;

    virtual ~ObjectSpawner() = default;

    void createSphere();

    void createCube();
};

#endif // OBJECT_SPAWNER_H
