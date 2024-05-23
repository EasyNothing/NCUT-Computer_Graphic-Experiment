//ÒýÓÃÍ·ÎÄ¼þ
#define _USE_MATH_DEFINES
#include <gl/glut.h>
#include <cmath>
#include <stdio.h>



void RenderACircle(float radius = 0.5, int numofDot = 30)
{
	glBegin(GL_POINTS);
	glVertex2f(0, 0);

	for (int i = 0; i < numofDot; i++) {
		float degree = 2.0f * M_PI * i / numofDot;
		float x = radius * cos(degree);
		float y = radius * sin(degree);
		glVertex2f(x, y);
	}
	glEnd();
}

void RenderAHelix(float radiusInner = 0.1, float radiusOuter = 0.8, int numofDot = 50)

{
	glBegin(GL_POINTS);
	glVertex2f(0, 0);

	for (int i = 0; i < numofDot; i++) {
		float degree = 2.0f * M_PI * i / 30;
		float x = (radiusInner + i * (radiusInner + radiusOuter) / numofDot) * cos(degree);
		float y = (radiusInner + i * (radiusInner + radiusOuter) / numofDot) * sin(degree);
		glVertex2f(x, y);
	}
	glEnd();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	RenderACircle(0.3);
	RenderACircle(0.5, 50);

	//RenderAHelix(0.1, 0.8);
	//RenderAHelix(0.01, 0.9, 100);

	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutCreateWindow("Simple");

	glutDisplayFunc(RenderScene);

	glutMainLoop();

	return 0;
}
