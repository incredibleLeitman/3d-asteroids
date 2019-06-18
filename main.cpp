#ifdef WIN32
    #define NOMINMAX // needed for windows to use std::min
#endif

#include <stdlib.h> // for exit
//#include <unistd.h> // for usleep
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "BaseObjects/CameraObject.h"
#include "BaseObjects/CollidableObject.h"
#include "BaseObjects/KinematicObject.h"
#include "BaseObjects/RenderObject.h"
#include "Defines.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"
#include "Util/TextureManager.h"

int window;

int width = 1920;
int height = 1080;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;

const GLuint ASTEROID_IMG_ID =  1;
const GLuint EARTH_IMG_ID =     2;
const GLuint COCKPIT_IMG_ID =   3;
const GLuint SUN_IMG_ID =       4;
const GLuint UNIVERSE_IMG_ID =  5;

// player looking direction
int moving = 0;         // flag that is true while mouse moves
int begin_x = 0;        // x value of mouse movement
int begin_y = 0;        // y value of mouse movement
GLfloat angle_y = 0;    // angle of spin around y axis of scene, in degrees
GLfloat angle_x = 0;    // angle of spin around x axis  of scene, in degrees

// world objects
ObjectSpawner *spawner = new ObjectSpawner();
std::vector<std::vector<float>> stars = std::vector<std::vector<float>>(count_stars);

std::shared_ptr<Object> root = std::make_shared<Object>("Root");
//std::shared_ptr<KinematicObject> player;
KinematicObject *player;

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, &timer, 1);
    player->update(1 / 60.0);
}

void resize(int new_width, int new_height) {
    // prevent division by zero
    if (height == 0) { height = 1; }

    glViewport(0, 0, new_width, new_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) {
    // Esc is exit

    // W and S is pitch
    // A and D is roll
    // Q and E is yaw

    // I and K are forward
    // J and L are sideways
    // U and O are up

    switch (key) {
        // exit
        case 27:
            glutDestroyWindow(window);
            exit(0);
            break;
            // Forward
        case 'i':
            player->linearThrust[2] = -1;
            break;
        case 'k':
            player->linearThrust[2] = 1;
            break;

            // Sideways
        case 'j':
            player->linearThrust[0] = -1;
            break;
        case 'l':
            player->linearThrust[0] = 1;
            break;

            // Up
        case 'u':
            player->linearThrust[1] = 1;
            break;
        case 'o':
            player->linearThrust[1] = -1;
            break;

            // Yaw
        case 'q':
            player->angularThrust[1] = 1;
            break;
        case 'e':
            player->angularThrust[1] = -1;
            break;

            // Roll
        case 'a':
            player->angularThrust[2] = 1;
            break;
        case 'd':
            player->angularThrust[2] = -1;
            break;

            // Pitch
        case 'w':
            player->angularThrust[0] = 1;
            break;
        case 's':
            player->angularThrust[0] = -1;
            break;

            // Emergency
        case ' ':
            player->angularVelocity[0] = 0;
            player->angularVelocity[1] = 0;
            player->angularVelocity[2] = 0;

            player->linearVelocity[0] = 0;
            player->linearVelocity[1] = 0;
            player->linearVelocity[2] = 0;
            break;
    }
}

void keyReleased(unsigned char key, int x, int y) {
    switch (key) {
        // Forward
        case 'i':
        case 'k':
            player->linearThrust[2] = 0;
            break;

            // Sideways
        case 'j':
        case 'l':
            player->linearThrust[0] = 0;
            break;

            // Up
        case 'u':
        case 'o':
            player->linearThrust[1] = 0;
            break;

            // Yaw
        case 'q':
        case 'e':
            player->angularThrust[1] = 0;
            break;

            // Roll
        case 'a':
        case 'd':
            player->angularThrust[2] = 0;
            break;

            // Pitch
        case 'w':
        case 's':
            player->angularThrust[0] = 0;
            break;
    }
}

static void specialKeyPressed(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            inc *= 1.5;
            break;
        case GLUT_KEY_DOWN:
            inc *= 0.75;
            break;
    }
}

void mouseButton(int button, int state, int x, int y) {
    // mouse Example code
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            moving = 1;
            begin_x = x;
            begin_y = y;

        }
        else if (state == GLUT_UP) {
            moving = 0;
        }
        break;

    default:
        break;
    }
}

void mouseMotion(int x, int y) {
    // mouse Example code
    if (moving) {
        angle_y = angle_y + (x - begin_x);
        angle_x = angle_x + (y - begin_y);
        if (angle_x > 360.0) angle_x -= 360.0;
        else if (angle_x < -360.0) angle_x += 360.0;
        if (angle_y > 360.0) angle_y -= 360.0;
        else if (angle_y < -360.0) angle_y += 360.0;

        begin_x = x;
        begin_y = y;
    }
}

void drawRect(float extentX, float extentY, float distZ, float topOffset) {
    glBegin(GL_QUADS);

    // Left
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, extentX);
    glTexCoord2f(1, 0);
    glVertex3f(-extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(-extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, extentY, extentX);

    // Front
    glTexCoord2f(0, 0);
    glVertex3f(-extentX, -extentY, distZ);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(-extentX, extentY, distZ - topOffset);

    // Right
    glTexCoord2f(0, 0);
    glVertex3f(extentX, -extentY, extentX);
    glTexCoord2f(1, 0);
    glVertex3f(extentX, -extentY, distZ);
    glTexCoord2f(1, 1);
    glVertex3f(extentX, extentY, distZ - topOffset);
    glTexCoord2f(0, 1);
    glVertex3f(extentX, extentY, extentX);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Greater FOV the faster the player moves
    gluPerspective(60 + std::min(player->linearVelocity.norm() * 100.0, 40.0), (float) width / (float) height, 0.1f,
                   10000.0f);

    gluLookAt(-sinf(RAD(angle_y)), sinf(RAD(angle_x)), cosf(RAD(angle_y)),
        0., 0., 0., 0., 1., 0.);

    hour += inc;
    day += inc / 24.0;
    hour = hour - ((int) (hour / 24)) * 24;
    day = day - ((int) (day / 365)) * 365;

    // draw "cockpit" before applying player->ovement
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    TextureManager::Inst()->bindTexture(COCKPIT_IMG_ID);

    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    drawRect(1.0, 0.5, -0.5, 0.4);
    glPopMatrix();

    std::dynamic_pointer_cast<CameraObject>(player->getChild("PlayerCamera"))->setCamera();

    // universe - the one above all...
    TextureManager::Inst()->bindTexture(UNIVERSE_IMG_ID);
    GLUquadric *sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 1000, 500, 500);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Stars
    /*glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < count_stars; i++) {
        glPushMatrix();
        glTranslatef(stars[i][0], stars[i][1], stars[i][2]);
        glutSolidSphere(0.1, 15, 15);
        glPopMatrix();
    }*/

    //std::cout << "containing elements in root: " << std::endl;
    glColor3f(1.0, 1.0, 1.0);
    for (auto &object : root->getChildren())
    {
        //std::cout << object->getName() << std::endl;
        for (auto &sub_object : object->getChildren())
        {
            //std::cout << "\t" << sub_object->getName() << " with type: " << typeid(*sub_object.get()).name() << std::endl;
            if (typeid(*sub_object.get()) == typeid(RenderObject))
            {
                // TODO: check color, img and stuff...
                //std::dynamic_pointer_cast<RenderObject>(sub_object)->render();

                glPushMatrix();
                Eigen::Vector3d pos = object->getTransform().col(3).head<3>();
                glTranslatef(pos.x(), pos.y(), pos.z());
                glutSolidSphere(0.1, 15, 15);
                glPopMatrix();


                double val = pos.x();
            }
        }
    }

    // ecliptic
    glRotatef(360 * day / 365.0, 0.0, 1.0, 0.0);
    glRotatef(15.0, 1.0, 0.0, 0.0);

    // sun
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 0.0);
    TextureManager::Inst()->bindTexture(SUN_IMG_ID);
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 1, 36, 72);
    glEnable(GL_LIGHTING);

    // earth
    // position around the sun
    glRotatef(360.0 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0);

    glPushMatrix();
    // rotate the earth on its axis
    glRotatef(360.0 * hour / 24.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    TextureManager::Inst()->bindTexture(EARTH_IMG_ID);
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 0.3, 36, 72);
    glPopMatrix();

    // moon
    glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    glColor3f(1, 1, 1);
    TextureManager::Inst()->bindTexture(ASTEROID_IMG_ID);
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 0.1, 36, 72);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void init() {
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 0.8, 0.6, 1.0};
    GLfloat mat_shininess[] = {15.0};
    GLfloat light_position[] = {0.0, 0.0, -8.0, 1.0};
    GLfloat light_diffuse[] = {0.0, 1.0, 1.0, 0.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // load textures
    TextureManager::Inst()->loadTexture("resources/asteroid.tga", ASTEROID_IMG_ID);
    TextureManager::Inst()->loadTexture("resources/earth.tga", EARTH_IMG_ID);
    TextureManager::Inst()->loadTexture("resources/cockpit.tga", COCKPIT_IMG_ID);
    TextureManager::Inst()->loadTexture("resources/sun.tga", SUN_IMG_ID);
    TextureManager::Inst()->loadTexture("resources/universe.tga", UNIVERSE_IMG_ID);

    // create objects
    spawner->createSphere();
    spawner->createCube();
    // ...

    // Generate some stars
    for (int i = 0; i < count_stars; i++) {
        stars[i] = std::vector<float>{ (Random::ZeroToOne() - 0.5f) * 100.0f,
                                      (Random::ZeroToOne() - 0.5f) * 100.0f,
                                      (Random::ZeroToOne() - 0.5f) * 100.0f };
    }

    //// render the stars
    //glColor3f(1.0, 1.0, 1.0);
    //for (int i = 0; i < count_stars; i++) {
    //    glPushMatrix();
    //    glTranslatef(stars[i][0], stars[i][1], stars[i][2]);
    //    glutSolidSphere(0.1, 15, 15);
    //    glPopMatrix();
    //}

    for (int i = 0; i < count_stars; i++) {
        //auto star = std::make_shared<KinematicObject>("Star" + std::to_string(i),
        //std::shared_ptr<KinematicObject> star(new KinematicObject("Star" + std::to_string(i),
        auto star = new KinematicObject("Star" + std::to_string(i),
            Eigen::Vector3d{
                (Random::ZeroToOne() - 0.5f) * 100.0f ,
                (Random::ZeroToOne() - 0.5f) * 100.0f ,
                (Random::ZeroToOne() - 0.5f) * 100.0f },
            Eigen::Vector3d::Zero(),
            Eigen::Vector3d::Zero());
        std::cout << "created star: " << star->getName() << std::endl;

        //auto render = std::make_shared<RenderObject>(star->getName());
        //star->addChild(render);
        star->addChild(std::make_shared<RenderObject>(star->getName() + "Renderer"));
        
        std::shared_ptr<KinematicObject> star_shared(star);
        root->addChild(star_shared);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    //glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    //resize(width, height); // LEM: should not be needed
}

int main(int argc, char **argv) {
    // Build the player object and its children
    /*player = std::make_shared<KinematicObject>("Player", Eigen::Vector3d{0.0, 0.0, 8.0},
                                               Eigen::Vector3d{25.0, 25.0, 25.0},
                                               Eigen::Vector3d{2.0, 2.0, 2.0});*/
    player = new KinematicObject("Player",
        Eigen::Vector3d{ 0.0, 0.0, 8.0 },
        Eigen::Vector3d{ 25.0, 25.0, 25.0 },
        Eigen::Vector3d{ 2.0, 2.0, 2.0 });
    player->addChild(std::make_shared<CollidableObject>("PlayerCollider", 5.0));
    player->addChild(std::make_shared<CameraObject>("PlayerCamera"));

    // Add the player to the root node
    std::shared_ptr<KinematicObject> sharedPlayer(player);
    root->addChild(sharedPlayer);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("3D Asteroids");
    glutDisplayFunc(&display);
    glutTimerFunc(1000 / 60.0, &timer, 1);
    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyReleased);
    glutSpecialFunc(&specialKeyPressed);
    glutMouseFunc(&mouseButton);
    glutMotionFunc(&mouseMotion);

    init();
    glutMainLoop();
    return 0;
}