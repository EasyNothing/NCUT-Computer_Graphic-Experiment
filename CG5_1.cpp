#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
//#pragma comment(lib,"opengl32.lib")
//#pragma comment(lib,"glu32.lib")
//#pragma comment(lib,"glut32.lib")

#define PI 3.1415926
int iWidth = 600;
int iHeight = 600;

float xRot = 0.0;
float yRot = 0.0;

void SetColor(int red, int green, int blue)
{
	glColor3ub(red, green, blue);
}

void SphereVertex(float theta, float phi, float radius, float* vertex) {
	vertex[0] = radius * cos(phi) * cos(theta);
	vertex[1] = radius * cos(phi) * sin(theta);
	vertex[2] = radius * sin(phi);
}

void RenderASphere(float fRadius, int iSlices = 30, int iStacks = 15) 
{
	for (int i = 0; i < iStacks; ++i) {
		float phi = PI / 2 - i * PI / iStacks;
		float phiNext = PI / 2 - (i + 1) * PI / iStacks;

		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= iSlices; ++j) {
			float theta = 2 * PI * j / iSlices;

			float vertex[3], nextVertex[3];
			SphereVertex(theta, phi, fRadius, vertex);
			SphereVertex(theta, phiNext, fRadius, nextVertex);

			glNormal3f(vertex[0], vertex[1], vertex[2]);
			glVertex3fv(vertex);

			glNormal3f(nextVertex[0], nextVertex[1], nextVertex[2]);
			glVertex3fv(nextVertex);
		}
		glEnd();
	}
	
}

void RenderSence()
{
	/**/glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotated(xRot, 1, 0, 0);
	glRotated(yRot, 0, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//RenderAHelix(10,60);
	RenderASphere(30, 30, 15);
	//glutWireTeapot(30);
	//glutSolidTeapot(20);
	//glutWireSphere(30, 50, 50);
	glPopMatrix();
	glutSwapBuffers();
}
void ProSpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		xRot += 5.0f;
	}
	if (key == GLUT_KEY_DOWN)
	{
		xRot -= 5.0f;
	}
	if (key == GLUT_KEY_LEFT)
	{
		yRot += 5.0f;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		yRot -= 5.0f;
	}
	glutPostRedisplay();
}
void initWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutInitWindowPosition(300, 300);
	glutInitWindowSize(iWidth, iHeight);
	glutCreateWindow("Simple");
}
void initBackground()
{
	glClearColor(1, 1, 1, 1);
}
void init()
{
	initWindow();
}
void output()
{
	//glMatrixMode(GL_PROJECTION);
	int iSize = 100;
	glOrtho(-iSize, iSize, -iSize, iSize, -iSize, iSize);
	glutSpecialFunc(ProSpecialKeys);
	glutDisplayFunc(RenderSence);
	glutMainLoop();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	output();
	return 0;
}

