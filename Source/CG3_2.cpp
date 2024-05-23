#include <gl/glut.h>


float fRotateTriY = 0; 
float fRotateTriX = 0; 
float fRotateQuadZ = 0;
float fRotateQuadX = 0;


float	fRotateQuad = 0;

void Init()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
}


void RenderMovingTris()
{
    glLoadIdentity();
    glTranslatef(-1.5f, 1.5f, -6.0f);
    glRotatef(fRotateTriY, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glLoadIdentity();
    glTranslatef(-1.5f, -1.5f, -6.0f);
    glRotatef(fRotateTriX, 1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

void RenderMovingQuads()
{
    glLoadIdentity();
    glTranslatef(1.5f, 1.5f, -6.0f);
    glRotatef(fRotateQuadZ, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glLoadIdentity();
    glTranslatef(1.5f, -1.5f, -6.0f);
    glRotatef(fRotateQuadX, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

void Reshape(int w, int h)
{
	if (0 == h)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
/*
void RenderATriangle()
{
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glRotatef(fRotateTri, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
*/

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//RenderATriangle();
	RenderMovingTris();
	RenderMovingQuads();

	glutSwapBuffers();

}

void TimerFunc(int value)
{
	//fRotateTri += 0.05f;
    fRotateTriY += 1.0f;
    fRotateTriX += 1.0f;
    fRotateQuadZ += 1.0f;
    fRotateQuadX += 1.0f;

	RenderScene();

    glutTimerFunc(16, TimerFunc, 0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Demo");

	glutReshapeFunc(Reshape);

	glutDisplayFunc(RenderScene);

    glutTimerFunc(16,TimerFunc, 0);

	Init();

	glutMainLoop();

	return 0;

}
