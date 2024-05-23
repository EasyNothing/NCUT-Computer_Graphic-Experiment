#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <cmath>

struct Point {
    int x, y;
};

int startX, startY, endX, endY;
bool isDragging = false;
GLfloat red = 1.0, green = 1.0, blue = 1.0;
int shapeType = 0;

void drawRectangle(int x1, int y1, int x2, int y2) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    glColor3f(red, green, blue);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void drawCircle(int centerX, int centerY, int radius) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.14159 / 180;
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();
}

void drawEllipse(int centerX, int centerY, int xRadius, int yRadius) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.14159 / 180;
        glVertex2f(centerX + xRadius * cos(angle), centerY + yRadius * sin(angle));
    }
    glEnd();
}

void drawShape() {
    switch (shapeType) {
    case 0:
        drawRectangle(startX, startY, endX, endY);
        break;
    case 1:
        drawLine(startX, startY, endX, endY);
        break;
    case 2:
        drawEllipse((startX + endX) / 2, (startY + endY) / 2, abs(startX - endX) / 2, abs(startY - endY) / 2);
        break;
    case 3:
        drawCircle(startX, startY, sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY)) / 2);
        break;
    default:
        break;
    }
}

void display() {
    if (!isDragging) {
        drawShape();
    }
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startX = x;
        startY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        endX = startX;
        endY = startY;
        isDragging = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && isDragging) {
        endX = x;
        endY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        isDragging = false;
        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (isDragging)
            return;
        std::ofstream outFile("points.txt");
        if (outFile.is_open()) {
            outFile << startX << " " << startY << " " << endX << " " << endY << std::endl;
            outFile.close();
            std::cout << "Points saved to file 'points.txt'" << std::endl;
        }
        else {
            std::cerr << "Unable to open file for saving!" << std::endl;
        }
    }
}

void motion(int x, int y) {
    if (isDragging) {
        endX = x;
        endY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        glutPostRedisplay();
    }
}

void colorMenu(int value) {
    switch (value) {
    case 0:
        red = 1.0;
        green = 1.0;
        blue = 1.0;
        break;
    case 1:
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case 2:
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case 3:
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    case 4:
        exit(0);
        break;
    }
}

void shapeMenu(int value) {
    shapeType = value;
}

void readFile() {
    std::ifstream inFile("points.txt");
    if (inFile.is_open()) {
        inFile >> startX >> startY >> endX >> endY;
        inFile.close();
        std::cout << "Points loaded from file 'points.txt'" << std::endl;
    }
    else {
        std::cerr << "File 'points.txt' not found or unable to open for reading!" << std::endl;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Draw");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    int colorMenuId = glutCreateMenu(colorMenu);
    glutAddMenuEntry("White", 0);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Exit", 4);

    int shapeMenuId = glutCreateMenu(shapeMenu);
    glutAddMenuEntry("Rectangle", 0);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Ellipse", 2);
    glutAddMenuEntry("Circle", 3);

    glutCreateMenu(colorMenu);
    glutAddSubMenu("Color", colorMenuId);
    glutAddSubMenu("Shape", shapeMenuId);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    readFile();

    glutMainLoop();
    return 0;
}
