#include <stdlib.h> // for exit
//#include <unistd.h> // for usleep
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Defines.h"
#include "RandomRange.h"
#include "Object.h"
#include "TextureManager.h"
#include "CollidableObject.h"

int window;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;

GLuint ASTEROID_IMG_ID;

const int count_stars = 30; // LEM: TODO: ask @KB: define global variable oder #define?
std::vector<std::vector<float>> stars = std::vector<std::vector<float>>(count_stars);
CollidableObject player = CollidableObject(Eigen::Vector3d{25.0, 25.0, 25.0}, Eigen::Vector3d{2.0, 2.0, 2.0}, 5.0);

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60.0, &timer, 1);
    player.update(1 / 60.0);
}

void resize(int width, int height) {
    // prevent division by zero
    if (height == 0) { height = 1; }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, (float) width / (float) height, 0.1f, 100.0f);
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
            player.linearThrust[2] = -1;
            break;
        case 'k':
            player.linearThrust[2] = 1;
            break;

            // Sideways
        case 'j':
            player.linearThrust[0] = -1;
            break;
        case 'l':
            player.linearThrust[0] = 1;
            break;

            // Up
        case 'u':
            player.linearThrust[1] = 1;
            break;
        case 'o':
            player.linearThrust[1] = -1;
            break;

            // Yaw
        case 'q':
            player.angularThrust[1] = 1;
            break;
        case 'e':
            player.angularThrust[1] = -1;
            break;

            // Roll
        case 'a':
            player.angularThrust[2] = 1;
            break;
        case 'd':
            player.angularThrust[2] = -1;
            break;

            // Pitch
        case 'w':
            player.angularThrust[0] = 1;
            break;
        case 's':
            player.angularThrust[0] = -1;
            break;

            // Emergency
        case ' ':
            player.angularVelocity[0] = 0;
            player.angularVelocity[1] = 0;
            player.angularVelocity[2] = 0;

            player.linearVelocity[0] = 0;
            player.linearVelocity[1] = 0;
            player.linearVelocity[2] = 0;

    }
}

void keyReleased(unsigned char key, int x, int y) {
	// LEM: TODO: ask @KB: fallthrough ugly?
	switch (key) {
		// Forward
	case 'i':
		//player.linearThrust[2] = 0;
		//break;
	case 'k':
		player.linearThrust[2] = 0;
		break;

		// Sideways
	case 'j':
		//player.linearThrust[0] = 0;
		//break;
	case 'l':
		player.linearThrust[0] = 0;
		break;

		// Up
	case 'u':
		//player.linearThrust[1] = 0;
		//break;
	case 'o':
		player.linearThrust[1] = 0;
		break;

		// Yaw
	case 'q':
		//player.angularThrust[1] = 0;
		//break;
	case 'e':
		player.angularThrust[1] = 0;
		break;

		// Roll
	case 'a':
		//player.angularThrust[2] = 0;
		//break;
	case 'd':
		player.angularThrust[2] = 0;
		break;

		// Pitch
	case 'w':
		//player.angularThrust[0] = 0;
		//break;
	case 's':
		player.angularThrust[0] = 0;
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

void mouseButton(int button, int state, int x, int y)
{
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

void applyPlayerMovement()
{
	// Translate according to player variables
	float matrix[16];

	int accessorAdd = 0;
	for (int i = 0; i < 12; i++) {
		if ((i + 1) % 4 == 0) {
			matrix[i] = 0;
			accessorAdd++;
		}
		else {
			matrix[i] = player.basis.inverse()(i - accessorAdd);
		}
		if (debug_output) std::cout << matrix[i] << std::endl;
	}
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;

	glMultMatrixf(matrix);

	glTranslatef(-player.position[0], -player.position[1], -player.position[2]);
}

void displayTest()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	applyPlayerMovement();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	if (TextureManager::Inst()->BindTexture(ASTEROID_IMG_ID) == false)
		std::cout << "binding texture failed..." << std::endl;

	glBegin(GL_QUADS);
	// front face
	//GLfloat fac = 2.0f;
	//GLfloat fac = .5f;
	GLfloat fac = 1.0f;
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(fac, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(fac, fac); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, fac); glVertex3f(-1.0f, 1.0f, 1.0f);
	// back face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// top face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glEnd();
	/*glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//glBindTexture(GL_TEXTURE_2D, textures[1]);
	if (TextureManager::Inst()->BindTexture(ASTEROID_IMG_ID) == false)
		std::cout << "binding texture failed..." << std::endl;
	glBegin(GL_QUADS);

	// bottom face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// left face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    hour += inc;
    day += inc / 24.0;
    hour = hour - ((int) (hour / 24)) * 24;
    day = day - ((int) (day / 365)) * 365;

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

	if (TextureManager::Inst()->BindTexture(ASTEROID_IMG_ID) == false)
		std::cout << "binding texture failed..." << std::endl;

	glEnd();
	glDisable(GL_TEXTURE_2D);

    // sun
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(1.0, 15, 15);
    glEnable(GL_LIGHTING);

    // earth
    // position around the sun
    glRotatef(360.0 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0);

    glPushMatrix();
    // rotate the earth on its axis
    glRotatef(360.0 * hour / 24.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();

    // moon
    glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    glColor3f(0.3f, 0.7f, 0.3f);
    glutSolidSphere(0.1f, 10, 10);

    glutSwapBuffers();
}

void init(int width, int height) {
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

	if (TextureManager::Inst()->LoadTexture("resources/asteroid.tga", ASTEROID_IMG_ID) == false)
		std::cout << "loading texture failed..." << std::endl;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    resize(width, height);
}

int main(int argc, char **argv) {
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
    //glutDisplayFunc(&display);
	glutDisplayFunc(&displayTest);

    glutTimerFunc(1000 / 60.0, &timer, 1);

    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyReleased);
    glutSpecialFunc(&specialKeyPressed);
	glutMouseFunc(&mouseButton);
	glutMotionFunc(&mouseMotion);

    init(640, 480);
	glutFullScreen();
    glutMainLoop();
    return 0;
}