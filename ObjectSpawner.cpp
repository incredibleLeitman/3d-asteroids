#include "BaseObjects/KinematicObject.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"

KinematicObject * ObjectSpawner::createSphere(std::string name, int index, GLuint texId, GLfloat r, GLfloat g, GLfloat b, GLdouble radius) {
    //auto sphere = std::make_shared<KinematicObject>("Star" + std::to_string(i),
    auto sphere = new KinematicObject(name + std::to_string(index),
        Eigen::Vector3d{
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f },
            Eigen::Vector3d::Zero(),
            Eigen::Vector3d::Zero());
    //std::cout << "created sphere: " << star->getName() << std::endl;

    sphere->addChild(std::make_shared<SphereRenderObject>(sphere->getName() + "Renderer",
        texId, Random::Range(218, 255), Random::Range(244, 255), Random::Range(0, 100), radius));
    return sphere;
}

KinematicObject * ObjectSpawner::createCube(std::string name, int index, GLuint texId, GLfloat r, GLfloat g, GLfloat b) {
    //auto cube = std::make_shared<KinematicObject>("Star" + std::to_string(i),
    auto cube = new KinematicObject(name + std::to_string(index),
        Eigen::Vector3d{
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f },
            Eigen::Vector3d::Zero(),
            Eigen::Vector3d::Zero());
    //std::cout << "created sphere: " << star->getName() << std::endl;

    // TODO: implement
    /*cube->addChild(std::make_shared<RenderObject>(cube->getName() + "Renderer",
        texId, Random::Range(218, 255), Random::Range(244, 255), Random::Range(0, 100)));*/
    return cube;
}