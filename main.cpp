#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h> // for exit
#include <unistd.h> // for usleep

int window;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60.0, &timer, 1);
}

void resize(int width, int height) {
    // prevent division by zero
    if (height == 0) { height = 1; }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    switch (key) {
        case 27:
            glutDestroyWindow(window);
            exit(0);
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    hour += inc;
    day += inc / 24.0;
    hour = hour - ((int) (hour / 24)) * 24;
    day = day - ((int) (day / 365)) * 365;

    glTranslatef(0.0, 0.0, -8.0);

    glRotatef(360 * day / 365.0, 0.0, 1.0, 0.0);

    // ecliptic
    glRotatef(15.0, 1.0, 0.0, 0.0);

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    resize(width, height);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("foo");
    glutDisplayFunc(&display);

    glutTimerFunc(1000 / 60.0, &timer, 1);

    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    init(640, 480);
    glutMainLoop();
    return 0;
}