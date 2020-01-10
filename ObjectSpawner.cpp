#include <utility>

#include <utility>

#include "BaseObjects/KinematicObject.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"
#include "BaseObjects/CollidableObject.h"

const float OBJECT_RANGE = 150.0f;

KinematicObject* ObjectSpawner::createSphere(std::string name, GLuint texId,
    GLfloat r, GLfloat g, GLfloat b,
    GLdouble radius_min, GLdouble radius_max,
    float rotspeed, float rot_x, float rot_y, float rot_z) {
    auto sphere = new KinematicObject(std::move(name),
        Eigen::Vector3d{
            // random position within world space
            (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE,
            (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE,
            (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE },
            Eigen::Vector3d::Zero(),
            Eigen::Vector3d::Zero());

    sphere->angularThrust = Eigen::Vector3d{ rot_x, rot_y, rot_z };
    sphere->angularVelocity = Eigen::Vector3d{ rotspeed, rotspeed, rotspeed };
    sphere->linearVelocity = Eigen::Vector3d::Zero();

    GLfloat r_col_r = r / 255.0f;
    GLfloat r_col_g = g / 255.0f;
    GLfloat r_col_b = b / 255.0f;
    float val = Random::RangeF(radius_min, radius_max);
    GLdouble r_radius = val;

    sphere->addChild(std::make_shared<SphereRenderObject>(sphere->getName() + "Renderer",
        texId,
        r_col_r, r_col_g, r_col_b,
        r_radius));

    sphere->addChild(std::make_shared<CollidableObject>(sphere->getName() + "Collider", r_radius));

    return sphere;
}

KinematicObject* ObjectSpawner::createCube(std::string name, GLuint texId,
    GLfloat r, GLfloat g, GLfloat b,
    GLdouble dim_min, GLdouble dim_max,
    float rotspeed, float rot_x, float rot_y, float rot_z) {
    auto cube = new KinematicObject(std::move(name),
        Eigen::Vector3d{
                (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE,
                (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE,
                (Random::ZeroToOne() - 0.5f) * OBJECT_RANGE },
                Eigen::Vector3d::Zero(),
                Eigen::Vector3d::Zero());

    cube->angularThrust = Eigen::Vector3d{ rot_x, rot_y, rot_z };
    cube->angularVelocity = Eigen::Vector3d{ rotspeed, rotspeed, rotspeed };
    cube->linearVelocity = Eigen::Vector3d::Zero();

    GLfloat r_col_r = r / 255.0f;
    GLfloat r_col_g = g / 255.0f;
    GLfloat r_col_b = b / 255.0f;
    float val = Random::RangeF(dim_min, dim_max);
    GLdouble r_dim = val;

    cube->addChild(std::make_shared<CubeRenderObject>(cube->getName() + "Renderer",
        texId, r_col_r, r_col_g, r_col_b, r_dim));

    cube->addChild(std::make_shared<CollidableObject>(cube->getName() + "Collider", r_dim));

    return cube;
}