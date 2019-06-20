#include <utility>

#include "BaseObjects/KinematicObject.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"
#include "BaseObjects/CollidableObject.h"

KinematicObject *ObjectSpawner::createSphere(std::string name, GLuint texId,
                                             GLfloat r, GLfloat g, GLfloat b,
                                             GLdouble radius_min, GLdouble radius_max,
                                             float rotspeed, float rot_x, float rot_y, float rot_z) {
    auto sphere = new KinematicObject(std::move(name),
                                      Eigen::Vector3d{
                                              // random position within world space
                                              // TODO: Move parameters to Defines
                                              (Random::ZeroToOne() - 0.5f) * 100.0f,
                                              (Random::ZeroToOne() - 0.5f) * 100.0f,
                                              (Random::ZeroToOne() - 0.5f) * 100.0f},
                                      Eigen::Vector3d::Zero(),
                                      Eigen::Vector3d::Zero());

    sphere->angularThrust = Eigen::Vector3d{rot_x, rot_y, rot_z};
    sphere->angularVelocity = Eigen::Vector3d{rotspeed, rotspeed, rotspeed};
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

KinematicObject *ObjectSpawner::createCube(std::string name, GLuint texId,
                                           GLfloat r, GLfloat g, GLfloat b) {
    auto cube = new KinematicObject(name,
                                    Eigen::Vector3d{
                                            (Random::ZeroToOne() - 0.5f) * 100.0f,
                                            (Random::ZeroToOne() - 0.5f) * 100.0f,
                                            (Random::ZeroToOne() - 0.5f) * 100.0f},
                                    Eigen::Vector3d::Zero(),
                                    Eigen::Vector3d::Zero());

    // TODO: implement
    /*cube->addChild(std::make_shared<RenderObject>(cube->getName() + "Renderer",
        texId, Random::Range(218, 255), Random::Range(244, 255), Random::Range(0, 100)));*/
    return cube;
}