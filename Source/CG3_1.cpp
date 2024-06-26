#include <GL/glut.h>
#include <math.h>

// typedef GLint int;

float fM[3][3];

typedef float Matrix3x3[3][3];
Matrix3x3 temp;

//float temp[3][3];

Matrix3x3 matComposite;

static bool bWire = false;
static bool bTranslate = false;
static bool bScale = false;

static int iType = 1;

///////////////////////////////////////////////////////////

struct Point2D
{
	float x, y;
};

Point2D vert[3] = {
	{0, 0},
	{20, 20},
	{40, 0}
};

void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	int row, col;
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			matIdent3x3[row][col] = (row == col);
		}
	}
}

void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	int row, col;
	Matrix3x3 temp;
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			temp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
		}
	}
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			m2[row][col] = temp[row][col];
		}
	}
}

void Translate2D(float tx, float ty)
{
	Matrix3x3 matTransl;
	matrix3x3SetIdentity(matTransl);
	matTransl[0][2] = tx;
	matTransl[1][2] = ty;
	matrix3x3PreMultiply(matTransl, matComposite);
}

void Scale2D(float sx, float sy, Point2D fixedPt)
{
	Translate2D(-fixedPt.x, -fixedPt.y);

	Matrix3x3 matScale;
	matrix3x3SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[1][1] = sy;

	matrix3x3PreMultiply(matScale, matComposite);

	Translate2D(fixedPt.x, fixedPt.y);
}

void Rotate2D(Point2D fixedPt, float theta)
{
	Point2D center = { 0.0f, 0.0f };
	Translate2D(-center.x, -center.y);

	float rad = theta * (3.14159 / 180.0);

	Matrix3x3 matRot;
	matrix3x3SetIdentity(matRot);
	matRot[0][0] = cos(rad);
	matRot[0][1] = -sin(rad);
	matRot[1][0] = sin(rad);
	matRot[1][1] = cos(rad);

	matrix3x3PreMultiply(matRot, matComposite);

	Translate2D(center.x, center.y);
}



void RenderTriangle(Point2D* verts)
{
	int k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	glEnd();
}

void TransformVerts2D(int nVerts, Point2D* verts)
{
	GLint k;
	GLfloat temp1, temp2;
	for (k = 0; k < nVerts; k++)
	{
		temp1 = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		temp2 = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
		verts[k].x = temp1;
		verts[k].y = temp2;
	}
}

// Called to draw scene
GLfloat	rtri;
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	if (bWire)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 70);
	glVertex2f(0, -70);
	glVertex2f(70, 0);
	glVertex2f(-70, 0);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	RenderTriangle(vert);


	glutSwapBuffers();
}


///////////////////////////////////////////////////////////
// Setup the rendering state
void InitGL(void)
{
	// Set clear color to blue
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


///////////////////////////////////////////////////////////
// Called by GLUT library when the window has chanaged size
void Reshape(int w, int h)
{
	GLfloat aspectRatio;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKey(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		bWire = !bWire;
	}

	if (key == 't' || key == 'T')
	{
		bTranslate = !bTranslate;
		if (bTranslate)
		{
			matrix3x3SetIdentity(matComposite);
			Translate2D(-50, -50);
			TransformVerts2D(3, vert);
		}
		else
		{
			matrix3x3SetIdentity(matComposite);
			Translate2D(50, 50);
			TransformVerts2D(3, vert);
		}

	}

	if (key == 'r' || key == 'R')
	{
		matrix3x3SetIdentity(matComposite);
		Rotate2D({ 0, 0 }, 45.0);
		TransformVerts2D(3, vert);
	}

	if (key == 's')
	{
		matrix3x3SetIdentity(matComposite);
		Scale2D(1.0 / 1.5, 1.0 / 1.5, { 0, 0 });
		TransformVerts2D(3, vert);
	}

	if (key == 'S')
	{
		matrix3x3SetIdentity(matComposite);
		Scale2D(1.5, 1.5, { 0, 0 });
		TransformVerts2D(3, vert);
	}

	glutPostRedisplay();
}

void mySpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		iType = 1;
	}
	if (key == GLUT_KEY_F2)
	{
		iType = 2;
	}
	if (key == GLUT_KEY_F3)
	{
		iType = 3;
	}

	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		iType++;
		if (iType > 3)
		{
			iType = 1;
		}
	}

	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		exit(0);
	}

	glutPostRedisplay();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLRect");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);

	glutKeyboardFunc(myKey);
	glutSpecialFunc(mySpecialKey);
	glutMouseFunc(myMouse);

	InitGL();

	glutMainLoop();

	return 0;
}


