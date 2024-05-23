#include <GL/glut.h>


void SetupRC() {
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_LIGHTING);    

    
    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    
    GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);  

    glEnable(GL_COLOR_MATERIAL); 
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void ChangeSize(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) {
        glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 100.0, -100.0);
    }
    else {
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 100.0, -100.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    gluLookAt(0.0f, 0.0f, 100.0f,  
        0.4f, 0.4f, 0.4f,    
        0.0f, 1.0f, 0.0f);   

    // 茶壶
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); 
    glTranslatef(-30.0f, 0.0f, 0.0f);
    glutSolidTeapot(10.0f);
    glPopMatrix();

    // 球体
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidSphere(10.0f, 50, 50);
    glPopMatrix();

    // 立方体
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); 
    glTranslatef(30.0f, 0.0f, 0.0f);
    glutSolidCube(20.0f);
    glPopMatrix();

    //甜甜圈
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 30.0f, 0.0f);
    glutSolidTorus(5.0f, 10.0f, 50, 50);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple");

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

    SetupRC();
    glutMainLoop();

    return 0;
}
