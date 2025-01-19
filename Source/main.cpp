#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cloudPosition = -1.2f;
float birdX = -1.0f;
float birdY = -0.8f;

void initGL() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(-0.8f, 0.8f, 0.1f);

    // Draw Cloud
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(cloudPosition - 0.1f, 0.5f, 0.1f);
    drawCircle(cloudPosition, 0.5f, 0.15f);
    drawCircle(cloudPosition + 0.1f, 0.5f, 0.1f);

    // Draw Bird
    glColor3f(0.0f, 0.0f, 0.0f);
    drawTriangle(birdX, birdY, birdX + 0.05f, birdY + 0.05f, birdX + 0.1f, birdY);

    glutSwapBuffers();
}

void update(int value) {
    // Update Cloud Position
    cloudPosition += 0.01f;
    if (cloudPosition > 1.2f) {
        cloudPosition = -1.2f;
    }

    // Update Bird Position
    birdX += 0.01f;
    birdY += 0.01f;
    if (birdX > 1.0f || birdY > 1.0f) {
        birdX = -1.0f;
        birdY = -0.8f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1300, 650);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("July Revolution Rendition");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    initGL();
    glutMainLoop();
    return 0;
}
