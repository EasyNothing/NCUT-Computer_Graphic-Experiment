#include <GL/glut.h>
#include <cmath>
#define M_PI 3.1415926

GLfloat lightPos[] = { 2.0f, 2.0f, 2.0f, 1.0f };
GLfloat angle = 0.0f;
bool isMoving = true;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 4.0, 5.0,  
        0.0, 0.0, 0.0,  
        0.0, 1.0, 0.0); 

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(1.5, 0.0, 0.0);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(-1.5, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0, 1.5, 0.0);
    glutSolidTorus(0.2, 0.5, 20, 20);
    glPopMatrix();

    lightPos[0] = 2.0f * cos(angle);
    lightPos[2] = 2.0f * sin(angle);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    if(isMoving){
        angle += 0.05f;
        if (angle > 2 * M_PI) {
            angle -= 2 * M_PI;
        }
        glutPostRedisplay();
    }

    glutTimerFunc(16, timer, 0);
}

void keyPress(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        isMoving = !isMoving;
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Scene with Moving Light");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPress);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
