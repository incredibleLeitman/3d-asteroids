#include "BaseObjects/KinematicObject.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"

#include <iostream>

KinematicObject * ObjectSpawner::createSphere(std::string name, GLuint texId,
    GLfloat r, GLfloat g, GLfloat b,
    GLdouble radius_min, GLdouble radius_max,
    float rotspeed, float rot_x, float rot_y, float rot_z) {
    //auto sphere = std::make_shared<KinematicObject>("Star" + std::to_string(i),
    auto sphere = new KinematicObject(name,
        Eigen::Vector3d{
            // random position within world space
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f ,
            (Random::ZeroToOne() - 0.5f) * 100.0f },
            Eigen::Vector3d::Zero(),
            Eigen::Vector3d::Zero());

    GLfloat r_col_r = r / 255.0f;
    GLfloat r_col_g = g / 255.0f;
    GLfloat r_col_b = b / 255.0f;
    float val = Random::RangeF(radius_min, radius_max);
    GLdouble r_radius = val;

    /*std::cout << "created sphere: " << sphere->getName() << std::endl;
    std::cout << "\tr_radius: " << r_radius << std::endl;
    std::cout << "\tr_col_r: " << r_col_r << std::endl;
    std::cout << "\tr_col_g: " << r_col_g << std::endl;
    std::cout << "\tr_col_b: " << r_col_b << std::endl;*/

    sphere->addChild(std::make_shared<SphereRenderObject>(sphere->getName() + "Renderer",
        texId,
        r_col_r, r_col_g, r_col_b,
        r_radius,
        rotspeed, rot_x, rot_y, rot_z));
    return sphere;
}

KinematicObject * ObjectSpawner::createCube(std::string name, GLuint texId,
    GLfloat r, GLfloat g, GLfloat b) {
    //auto cube = std::make_shared<KinematicObject>("Star" + std::to_string(i),
    auto cube = new KinematicObject(name,
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