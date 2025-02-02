#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
using namespace std;

// Cloud positions and speeds
float cloud1Pos = 200.0f;
float cloud2Pos = 400.0f;
float cloud3Pos = 600.0f;
float cloud4Pos = 0.0f;
float cloud5Pos = 980.0f;

float cloud1Speed = 0.05f;
float cloud2Speed = 0.06f;
float cloud3Speed = 0.05f;
float cloud4Speed = 0.06f;
float cloud5Speed = 0.06f;

// Tank position and speed
float tankPos = -550.0f;
float tankSpeed = 0.03f;

void init(void)
{
    glClearColor(0.53, 0.81, 0.98, 0.0); // Set sky color to a light blue
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000, 0.0, 600); // Define window size
}

// Function to draw the road
void drawRoad()
{
    // Road
    glColor3ub(50, 50, 50); // Dark road
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(1000, 0);
    glVertex2d(1000, 150); // Height of the road
    glVertex2d(0, 150);
    glEnd();

    // Road divider
    glColor3ub(255, 255, 255); // White divider
    for (int i = 0; i <= 1000; i += 60) // Create thinner divider blocks
    {
        glBegin(GL_QUADS); // Use QUADS to create a block for the divider
        glVertex2d(i, 75);       // Bottom left of the block
        glVertex2d(i + 40, 75);  // Bottom right of the block
        glVertex2d(i + 40, 85);  // Top right of the block
        glVertex2d(i, 85);       // Top left of the block
        glEnd();
    }
}

// cloud positions
void updateCloudPositions()
{
    cloud1Pos += cloud1Speed;
    cloud2Pos += cloud2Speed;
    cloud3Pos += cloud3Speed;
    cloud4Pos += cloud4Speed;
    cloud5Pos += cloud5Speed;

    // Reset position if cloud moves off screen (wrap around effect)
    if (cloud1Pos > 1000) cloud1Pos = -200;
    if (cloud2Pos > 1000) cloud2Pos = -200;
    if (cloud3Pos > 1000) cloud3Pos = -200;
    if (cloud4Pos > 1000) cloud4Pos = -200;
    if (cloud5Pos > 1000) cloud5Pos = -200;

    glutPostRedisplay();  // Trigger a redraw of the scene
}

// Function to update the tank position
void updateTankPosition()
{
    tankPos += tankSpeed;

    // Reset position if tank moves off the screen (wrap around effect)
    if (tankPos > 500) tankPos = -550.0f;

    glutPostRedisplay();  // Trigger a redraw of the scene
}

// All the animations
void idle()
{
    updateCloudPositions();  // Update cloud positions
    updateTankPosition();    // Update tank position
}

// Function to draw the cloud
void drawCloud(int x, int y)
{
    glColor3ub(255, 255, 255); // Cloud color (white)

    //first circle (bottom-left)
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(x + cos(angle) * 20, y + sin(angle) * 20);
    }
    glEnd();

    // second circle
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(x + 30 + cos(angle) * 20, y + sin(angle) * 20);
    }
    glEnd();

    // third circle
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(x + 60 + cos(angle) * 20, y + sin(angle) * 20);
    }
    glEnd();

    // fourth circle (top left)
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(x + 20 + cos(angle) * 20, y + 25 + sin(angle) * 20);
    }
    glEnd();

    // fifth circle (top right)
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(x + 50 + cos(angle) * 20, y + 20 + sin(angle) * 20);
    }
    glEnd();
}

// Function to draw the tank
void drawTank(float xOffset, float yOffset)
{
    // Tank body 1
    glBegin(GL_POLYGON);
    glColor3ub(34,36,34);
    glVertex2i(525 + xOffset, 325 + yOffset);
    glVertex2i(535 + xOffset, 325 + yOffset);
    glVertex2i(715 + xOffset, 325 + yOffset);
    glVertex2i(725 + xOffset, 325 + yOffset);
    glVertex2i(715 + xOffset, 360 + yOffset);
    glVertex2i(535 + xOffset, 360 + yOffset);
    glEnd();

    // Tank body 2
    glBegin(GL_QUADS);
    glColor3ub(50,56,6);
    glVertex2i(565 + xOffset, 350 + yOffset);
    glVertex2i(675 + xOffset, 350 + yOffset);
    glColor3ub(34,36,34);
    glVertex2i(675 + xOffset, 390 + yOffset);
    glVertex2i(565 + xOffset, 390 + yOffset);

    // Tank head
    glColor3ub(34,36,34);
    glVertex2i(600 + xOffset, 390 + yOffset);
    glVertex2i(640 + xOffset, 390 + yOffset);
    glVertex2i(640 + xOffset, 400 + yOffset);
    glVertex2i(600 + xOffset, 400 + yOffset);

    // Tank gun
    glColor3ub(34, 36, 34);
    glVertex2i(675 + xOffset, 365 + yOffset);
    glVertex2i(755 + xOffset, 370 + yOffset);
    glVertex2i(755 + xOffset, 380 + yOffset);
    glVertex2i(675 + xOffset, 385 + yOffset);
    glEnd();

    // Tank base
    glBegin(GL_POLYGON);
    glColor3ub(79,68,31);
    for(int i = 180; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(625 + xOffset + cos(angle) * 90, 325 + yOffset + sin(angle) * 35);
    }
    glEnd();

    // Wheel 1
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(555 + xOffset + cos(angle) * 10, 315 + yOffset + sin(angle) * 10);
    }
    glEnd();

    // Wheel 2
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(690 + xOffset + cos(angle) * 10, 315 + yOffset + sin(angle) * 10);
    }
    glEnd();

    // Wheel 3
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(583 + xOffset + cos(angle) * 12, 310 + yOffset + sin(angle) * 12);
    }
    glEnd();

    // Wheel 4
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(611 + xOffset + cos(angle) * 13, 305 + yOffset + sin(angle) * 13);
    }
    glEnd();

    // Wheel 5
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(639 + xOffset + cos(angle) * 13, 305 + yOffset + sin(angle) * 13);
    }
    glEnd();

    // Wheel 6
    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    for(int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        glVertex2f(667 + xOffset + cos(angle) * 12, 306 + yOffset + sin(angle) * 12);
    }
    glEnd();

    //glFlush();
}

void drawArmy(int x, int y) {
    // Face (Light Brown Square)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.52, 0.25);
    glVertex2i(x + 10, y + 30);
    glVertex2i(x + 30, y + 30);
    glVertex2i(x + 30, y + 50);
    glVertex2i(x + 10, y + 50);
    glEnd();

    // Helmet
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.0);
    for (int i = 0; i < 180; i++) {
        float angle = i * 3.14159f / 180;
        glVertex2f(x + 20 + 15 * cos(angle), y + 40 + 15 * sin(angle));  // size
    }
    glEnd();

    // Hand
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(x -2, y + 10);   // Bottom Left
    glVertex2i(x + 35, y + 10);  // Bottom Right
    glVertex2i(x + 35, y + 30);  // Top Right
    glVertex2i(x - 2, y + 30);  // Top Left
    glEnd();

    // Body Texture Darker Green
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.3, 0.0);
    glVertex2i(x + 5, y + 8);
    glVertex2i(x + 35, y + 8);
    glVertex2i(x + 35, y + 30);
    glVertex2i(x + 5, y + 30);
    glEnd();

    // Legs
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(x + 8, y - 8);
    glVertex2i(x + 18, y - 8);
    glVertex2i(x + 18, y + 10);
    glVertex2i(x + 8, y + 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(x + 22, y - 8);
    glVertex2i(x + 32, y - 8);
    glVertex2i(x + 32, y + 10);
    glVertex2i(x + 22, y + 10);
    glEnd();

    // Rifle body
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.3, 0.1);
    glVertex2i(x + 20, y + 16);
    glVertex2i(x + 70, y + 20);
    glVertex2i(x + 70, y + 25);
    glVertex2i(x + 20, y + 25);
    glEnd();

    // Over Hand
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(x + 4, y + 10);      // Bottom-left corner
    glVertex2i(x + 20, y + 15);      // Bottom-right corner
    glVertex2i(x + 20, y + 25); // Top-right corner
    glVertex2i(x + 4, y + 20); // Top-left corner
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with the sky color

    // Draw the road
    drawRoad();

    // Draw the clouds
    drawCloud(cloud1Pos, 450);
    drawCloud(cloud2Pos, 520);
    drawCloud(cloud3Pos, 500);
    drawCloud(cloud4Pos, 500);
    drawCloud(cloud5Pos, 500);

    // Draw the tank
    drawTank(tankPos, -180);

    drawArmy(100, 100);
    drawArmy(85, 80);
    drawArmy(70, 65);
    drawArmy(85, 40);
    drawArmy(65, 20);

    glFlush();
}

int main(int argc, char** argv)
{
    cout << endl << "July Revolution Rendition: Echos of freedom " << endl << endl;
    cout << endl << "=============================================" << endl << endl;
    cout << "COMPUTER GRAPHICS [G]" << endl ;
    cout << "Fall 2024-2025" << endl;
    cout << "Course Instructor: Dipta Justin Gomes" << endl << endl;
    cout << "Submitted by" << endl << endl;
    cout << "1. Salman Sayeed      [22-49006-3]" << endl;
    cout << "2. Kayjer Islam       [22-49005-3]" << endl;
    cout << "3. S.M.Nahid Hassan   [22-49026-3]" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);; // Double buffering for smooth rendering
    glutInitWindowSize(1200, 700); // Set landscape window size
    glutInitWindowPosition(200, 50); // Set window position
    glutCreateWindow("July Revolution Rendition: Echos of freedom");
    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
