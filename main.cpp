#include <stdlib.h> // for exit
//#include <unistd.h> // for usleep
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "BaseObjects/CollidableObject.h"
#include "Defines.h"
#include "BaseObjects/KinematicObject.h"
#include "ObjectSpawner.h"
#include "Util/RandomRange.h"
#include "Util/TextureManager.h"

int window;

int width;
int height;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;

const GLuint ASTEROID_IMG_ID = 1;
const GLuint EARTH_IMG_ID = 2;
const GLuint COCKPIT_IMG_ID = 3;
const GLuint SUN_IMG_ID = 4;

const int count_stars = 30; // LEM: TODO: ask @KB: define global variable oder #define?
std::vector<std::vector<float>> stars = std::vector<std::vector<float>>(count_stars);
std::shared_ptr<KinematicObject> player = std::make_shared<KinematicObject>("player", Eigen::Vector3d{25.0, 25.0, 25.0}, Eigen::Vector3d{2.0, 2.0, 2.0});

ObjectSpawner spawner = ObjectSpawner();

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60.0, &timer, 1);
    player->update(1 / 60.0);
}

void resize(int width, int height) {
    // prevent division by zero
    if (height == 0) { height = 1; }

    glViewport(0, 0, width, height);
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

    }
}

void keyReleased(unsigned char key, int x, int y) {
    // LEM: TODO: ask @KB: fallthrough ugly?
    switch (key) {
        // Forward
        case 'i':
            //player->linearThrust[2] = 0;
            //break;
        case 'k':
            player->linearThrust[2] = 0;
            break;

            // Sideways
        case 'j':
            //player->linearThrust[0] = 0;
            //break;
        case 'l':
            player->linearThrust[0] = 0;
            break;

            // Up
        case 'u':
            //player->linearThrust[1] = 0;
            //break;
        case 'o':
            player->linearThrust[1] = 0;
            break;

            // Yaw
        case 'q':
            //player->angularThrust[1] = 0;
            //break;
        case 'e':
            player->angularThrust[1] = 0;
            break;

            // Roll
        case 'a':
            //player->angularThrust[2] = 0;
            //break;
        case 'd':
            player->angularThrust[2] = 0;
            break;

            // Pitch
        case 'w':
            //player->angularThrust[0] = 0;
            //break;
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
    /*switch (button) {
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
    }*/
}

void mouseMotion(int x, int y) {
    // mouse Example code
    /*if (moving) {
        angle_y = angle_y + (x - begin_x);
        angle_x = angle_x + (y - begin_y);
        if (angle_x > 360.0) angle_x -= 360.0;
        else if (angle_x < -360.0) angle_x += 360.0;
        if (angle_y > 360.0) angle_y -= 360.0;
        else if (angle_y < -360.0) angle_y += 360.0;

        begin_x = x;
        begin_y = y;
    }*/
}

void applyPlayerMovement() {
    // Translate according to
    float matrix[16];
    Eigen::Matrix4d inverseTransform = player->getTransform().inverse();

    for (int i = 0; i < 12; i++) {
        if ((i + 1) % 4 == 0) {
            matrix[i] = 0;
        } else {
            matrix[i] = inverseTransform(i);
        }
        if (debug_output) std::cout << matrix[i] << std::endl;
    }

    // We don't want the translation part since the player is the camera, which is centered
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;

    glMultMatrixf(matrix);

    glTranslatef(-player->position[0], -player->position[1], -player->position[2]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Greater FOV the faster the player->moves
    gluPerspective(60 + std::min(player->linearVelocity.norm() * 100.0, 40.0), (float) width / (float) height, 0.1f,
                   10000.0f);

    hour += inc;
    day += inc / 24.0;
    hour = hour - ((int) (hour / 24)) * 24;
    day = day - ((int) (day / 365)) * 365;

    // draw "cockpit" before applying player->ovement
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    TextureManager::Inst()->bindTexture(COCKPIT_IMG_ID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.75f, -1.0f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.75f, -1.0f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(1.75f, -0.5f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-1.75f, -0.5f, -1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    applyPlayerMovement();

    // Stars
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < count_stars; i++) {
        glPushMatrix();
        glTranslatef(stars[i][0], stars[i][1], stars[i][2]);
        glutSolidSphere(0.1, 15, 15);
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);

    glRotatef(360 * day / 365.0, 0.0, 1.0, 0.0);

    // ecliptic
    glRotatef(15.0, 1.0, 0.0, 0.0);

    // set textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // sun
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    //glutSolidSphere(1.0, 15, 15);
    TextureManager::Inst()->bindTexture(SUN_IMG_ID);
    GLUquadric *sphere = gluNewQuadric();
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
    //glutSolidSphere(0.4, 10, 10);
    TextureManager::Inst()->bindTexture(EARTH_IMG_ID);
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 0.3, 36, 72);
    glPopMatrix();

    // moon
    glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    //glColor3f(0.3f, 0.7f, 0.3f);
    glColor3f(1, 1, 1);
    //glutSolidSphere(0.1f, 10, 10);
    TextureManager::Inst()->bindTexture(ASTEROID_IMG_ID);
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 0.1, 36, 72);

    glDisable(GL_TEXTURE_2D);

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

    // create objects
    spawner.createSphere();
    spawner.createCube();
    // ...

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    resize(width, height);
}

int main(int argc, char **argv) {
    player->addChild(std::make_shared<CollidableObject>("player->ollider", 5.0));

    for (int i = 0; i < count_stars; i++) {
        stars[i] = std::vector<float>{(Random::ZeroToOne() - 0.5f) * 100.0f,
                                      (Random::ZeroToOne() - 0.5f) * 100.0f,
                                      (Random::ZeroToOne() - 0.5f) * 100.0f};
    }


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
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

    width = 1920;
    height = 1080;

    init();
    glutMainLoop();
    return 0;
}