/*
July Revolution Rendition: Echos of freedom
=============================================

Keybinds:
A = Decrease the Tank speed
D = Increase the Tank speed
N = Switch to night sky
B = Switch to day sky
R = Toggle between rainy and clear sky

=============================================

COMPUTER GRAPHICS [G]
Fall 2024-2025
Course Instructor: Dipta Justin Gomes

Submitted by:
1. Salman Sayeed      [22-49006-3]
2. Kayjer Islam       [22-49005-3]
3. S.M.Nahid Hassan   [22-49026-3]
*/

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

float skyColor[4] = {0.53f, 0.81f, 0.98f, 0.0f}; // Default sky color (light blue)

// Cloud positions and speeds
float cloud1Pos = 200.0f;
float cloud2Pos = 400.0f;
float cloud3Pos = 600.0f;
float cloud4Pos = 0.0f;
float cloud5Pos = 980.0f;

float cloud1Speed = 0.04f;
float cloud2Speed = 0.04f;
float cloud3Speed = 0.04f;
float cloud4Speed = 0.04f;
float cloud5Speed = 0.04f;

// Tank position and speed
float tankPos = -550.0f;
float tankSpeed = 0.02f;

//gun flash effect
bool gunFlash = false;
int flashCounter = 0;
int flashSpeed = 500;

//Fire Flash effect
bool showFire = true; // Flag to control whether to show fire or not
int flashSpeedFire = 50; // Controls how fast the fire flashes (milliseconds)

// Raindrop positions and speed
const int numRaindrops = 1000;  // Number of raindrops
float raindropX[numRaindrops];   // Array to hold the x positions of raindrops
float raindropY[numRaindrops];   // Array to hold the y positions of raindrops
float raindropSpeed[numRaindrops]; // Array to hold the falling speed of each raindrop
bool isRaining = false; // Flag to control rain animation

void init(void)
{
    glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]); // Set initial background color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000, 0.0, 600); // Define window size

    for (int i = 0; i < numRaindrops; i++) {
        raindropX[i] = rand() % 1000; // Random x position
        raindropY[i] = rand() % 600;  // Random y position
        raindropSpeed[i] = (rand() % 5 + 2) / 100.0f*8; // Random falling speed
    }
}

// Raindrop update
void updateRaindrops() {
    for (int i = 0; i < numRaindrops; i++) {
        raindropY[i] -= raindropSpeed[i]; // Move raindrop down

        // If raindrop goes off screen, reset its position to the top
        if (raindropY[i] < 0) {
            raindropY[i] = 600;
            raindropX[i] = rand() % 1000;
        }
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

    if (isRaining) {
        updateRaindrops();  // Update raindrops if it's raining
    }

     flashCounter++;

    // Toggle the gun flash
    if (flashCounter >= flashSpeed) {
        gunFlash = !gunFlash;
        flashCounter = 0; // Reset counter
    }

    glutPostRedisplay();
}

void drawRaindrops() {
    glColor3ub(0, 0, 255); // Blue color for rain

    for (int i = 0; i < numRaindrops; i++) {
        glBegin(GL_LINES);
        glVertex2f(raindropX[i], raindropY[i]);
        glVertex2f(raindropX[i], raindropY[i] - 10); // Draw a short vertical line for each raindrop
        glEnd();
    }
}

//  draw cloud
void drawCloud(int x, int y){
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

// Function to draw the road
void drawRoad()
{
    // Road
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(1000, 0);
    glVertex2d(1000, 150); // Height of the road
    glVertex2d(0, 150);
    glEnd();

    // Road divider
    glColor3ub(255, 255, 255); // White
    for (int i = 0; i <= 1000; i += 60)
    {
        glBegin(GL_QUADS); // Use QUADS to create a block for the divider
        glVertex2d(i, 75);       // Bottom left of the block
        glVertex2d(i + 40, 75);  // Bottom right of the block
        glVertex2d(i + 40, 85);  // Top right of the block
        glVertex2d(i, 85);       // Top left of the block
        glEnd();
    }

    // Footpath
    glColor3ub(128, 128, 128); // Grey
    glBegin(GL_POLYGON);
    glVertex2d(0, 150);
    glVertex2d(1000, 150);
    glVertex2d(1000, 200);
    glVertex2d(0, 200);
    glEnd();

    // bricks
    glColor3ub(160, 160, 160);
    for (int i = 0; i <= 1000; i += 50)
    {
        glBegin(GL_QUADS);
        glVertex2d(i, 150);
        glVertex2d(i + 40, 150);
        glVertex2d(i + 45, 200);
        glVertex2d(i + 5, 200);
        glEnd();
    }

    //Drain
    glColor3ub(30, 30, 30); // Grey
    glBegin(GL_POLYGON);
    glVertex2d(0, 130);
    glVertex2d(1000, 130);
    glVertex2d(1000, 150);
    glVertex2d(0, 150);
    glEnd();

    glColor3ub(10, 10, 10);
    for (int i = 0; i <= 1000; i += 50)
    {
        glBegin(GL_QUADS);
        glVertex2d(i, 130);
        glVertex2d(i + 40, 130);
        glVertex2d(i + 40, 150);
        glVertex2d(i, 150);
        glEnd();
    }

}

//Function to draw the fence
void drawFence(int offsetX, int offsetY) {
    // Fence Loops
    glColor3ub(94, 94, 94);
    for (int i = 0; i <= 1000; i += 15) {  // Loop through every 50 units
        glBegin(GL_QUADS);
        glVertex2d(offsetX + i, offsetY + 320);
        glVertex2d(offsetX + i + 5, offsetY + 320);
        glVertex2d(offsetX + i + 5, offsetY + 280);
        glVertex2d(offsetX + i, offsetY + 280);
        glEnd();
    }

    // Top Bar
    glColor3ub(54, 54, 54);
    glBegin(GL_POLYGON);
    glVertex2d(offsetX + 0, offsetY + 320);    // bot left
    glVertex2d(offsetX + 1000, offsetY + 320);  //bot right
    glVertex2d(offsetX + 1000, offsetY + 330);  // top right
    glVertex2d(offsetX + 0, offsetY + 330);   //top left
    glEnd();

    // Bottom Bar
    glColor3ub(54, 54, 54);
    glBegin(GL_POLYGON);
    glVertex2d(offsetX + 0, offsetY + 270);
    glVertex2d(offsetX + 1000, offsetY + 270);
    glVertex2d(offsetX + 1000, offsetY + 280);
    glVertex2d(offsetX + 0, offsetY + 280);
    glEnd();
}

void drawBloodTank(float xOffset, float yOffset)
{
    glColor3f(1.0, 0.0, 0.0);  // Bright red color

    int segments = 30;

    // Modify the position of the blood drop to be relative to the tank
    // For example, position it near the gun of the tank or wherever you want the blood to come from
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(670 + xOffset, 370 + yOffset); // Adjusted center of the blood drop

    // Draw the circle (blood drop)
    for (int i = 0; i <= segments; i++) {
        float angle = (2 * 3.14159265359 * i) / segments;
        float dx = 6 * cos(angle);
        float dy = 7 * sin(angle);
        glVertex2i(670 + xOffset + dx, 370 + yOffset + dy);  // Adjusted coordinates for movement
    }
    glEnd();
}


// draw tank
void drawTank(float xOffset, float yOffset){
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

    //===================================================================================

    // Now, move the man with the tank
    int x = 560 + xOffset;  // Man's position adjusted by tank's position
    int y = 340 + yOffset;

    float angle = 85.0f;

    glPushMatrix();  // Save current transformation state

    // Move the origin of the drawing to the center of the man for rotation
    glTranslatef(x + 20, y + 25, 0);  // Translate to the center of the man
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate around the z-axis (in 2D)

    glTranslatef(-(x + 20), -(y + 25), 0);

    // Face (Light Brown Square)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.52, 0.25);
    glVertex2i(x + 10, y + 30);
    glVertex2i(x + 30, y + 30);
    glVertex2i(x + 30, y + 50);
    glVertex2i(x + 10, y + 50);
    glEnd();

    // Eyes (Black Rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 10, y + 45);
    glVertex2i(x + 30, y + 45);
    glVertex2i(x + 30, y + 55);
    glVertex2i(x + 10, y + 55);
    glEnd();

    // Hand (Rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.52, 0.25);
    glVertex2i(x - 2, y + 10);   // Bottom Left
    glVertex2i(x + 35, y + 10);  // Bottom Right
    glVertex2i(x + 35, y + 30);  // Top Right
    glVertex2i(x - 2, y + 30);  // Top Left
    glEnd();

    // Body
    glBegin(GL_QUADS);
    glColor3ub(255, 182, 193);  // Light pink color
    glVertex2i(x + 5, y + 8);
    glVertex2i(x + 35, y + 8);
    glVertex2i(x + 35, y + 30);
    glVertex2i(x + 5, y + 30);
    glEnd();

    // Legs
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 8, y - 8);
    glVertex2i(x + 18, y - 8);
    glVertex2i(x + 18, y + 10);
    glVertex2i(x + 8, y + 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 22, y - 8);
    glVertex2i(x + 32, y - 8);
    glVertex2i(x + 32, y + 10);
    glVertex2i(x + 22, y + 10);
    glEnd();

    glPopMatrix();
    drawBloodTank(xOffset - 85, yOffset);
}


//Gun flash
void drawGunFlash(int x, int y) {
    if (gunFlash) {
        glColor3f(1.0, 0.7, 0.0);  // Reddish-yellow color
        glBegin(GL_POLYGON);
        for(int i = 0; i <= 360; i++) {
            float angle = i * 3.1416 / 180;
            glVertex2f(x + cos(angle) *5, y + sin(angle) *5);
        }
        glEnd();
    }
}

//draw army
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

    drawGunFlash(x + 70, y + 22);

    // Over Hand
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(x + 4, y + 10);      // Bottom-left corner
    glVertex2i(x + 20, y + 15);      // Bottom-right corner
    glVertex2i(x + 20, y + 25); // Top-right corner
    glVertex2i(x + 4, y + 20); // Top-left corner
    glEnd();
}

//draw Tent
void drawTent(int offsetX, int offsetY)
{
    glBegin(GL_QUADS); // Tent body
    glColor3ub(85, 89, 67);
    glVertex2i(820 + offsetX, 490 + offsetY);
    glVertex2i(820 + offsetX, 540 + offsetY);
    glVertex2i(740 + offsetX, 540 + offsetY);
    glVertex2i(740 + offsetX, 490 + offsetY);
    glEnd();

    glBegin(GL_TRIANGLES); // Tent top
    glColor3ub(50, 55, 40);
    glVertex2i(830 + offsetX, 540 + offsetY);
    glVertex2i(780 + offsetX, 565 + offsetY);
    glVertex2i(730 + offsetX, 540 + offsetY);
    glEnd();

    glBegin(GL_LINES); // Tent ropes
    glColor3ub(85, 89, 67);
    glVertex2i(830 + offsetX, 540 + offsetY);
    glVertex2i(810 + offsetX, 500 + offsetY);

    glVertex2i(830 + offsetX, 540 + offsetY);
    glVertex2i(840 + offsetX, 480 + offsetY);

    glVertex2i(730 + offsetX, 540 + offsetY);
    glVertex2i(750 + offsetX, 500 + offsetY);

    glVertex2i(730 + offsetX, 540 + offsetY);
    glVertex2i(720 + offsetX, 480 + offsetY);
    glEnd();

    glBegin(GL_QUADS); // Tent door
    glColor3ub(0, 0, 0);
    glVertex2i(795 + offsetX, 490 + offsetY);
    glVertex2i(795 + offsetX, 525 + offsetY);
    glVertex2i(765 + offsetX, 525 + offsetY);
    glVertex2i(765 + offsetX, 490 + offsetY);
    glEnd();
}

//Barricade
void drawBarricade(int offsetX, int offsetY) {
    //Pole of the barricade
    glColor3ub(255, 110, 0);  // Dark orange
    glBegin(GL_QUADS);
    glVertex2i(65 + offsetX, 40 + offsetY);
    glVertex2i(78 + offsetX, 40 + offsetY);
    glVertex2i(78 + offsetX, 130 + offsetY);
    glVertex2i(65 + offsetX, 130 + offsetY);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(120 + offsetX, 40 + offsetY);
    glVertex2i(133 + offsetX, 40 + offsetY);
    glVertex2i(133 + offsetX, 130 + offsetY);
    glVertex2i(120 + offsetX, 130 + offsetY);
    glEnd();

    // Main body of the barricade
    glColor3ub(255, 165, 0);  // orange
    glBegin(GL_QUADS);
    glVertex2i(50 + offsetX, 100 + offsetY);  // Bottom left
    glVertex2i(150 + offsetX, 100 + offsetY); // Bottom
    glColor3ub(255, 135, 0);
    glVertex2i(150 + offsetX, 120 + offsetY); // Top right
    glVertex2i(50 + offsetX, 120 + offsetY);  // Top left
    glEnd();

    glColor3ub(255, 165, 0);
    glBegin(GL_QUADS);
    glVertex2i(50 + offsetX, 70 + offsetY);
    glVertex2i(150 + offsetX, 70 + offsetY);
    glColor3ub(255, 135, 0);
    glVertex2i(150 + offsetX, 90 + offsetY);
    glVertex2i(50 + offsetX, 90 + offsetY);
    glEnd();
}

void drawBarricade2(int offsetX, int offsetY) {
    //Pole of the barricade
    glColor3ub(255, 110, 0);  // Dark orange
    glBegin(GL_QUADS);
    glVertex2i(65 + offsetX, 50 + offsetY);
    glVertex2i(78 + offsetX, 55 + offsetY);
    glVertex2i(78 + offsetX, 145 + offsetY);
    glVertex2i(65 + offsetX, 140 + offsetY);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(120 + offsetX, 70 + offsetY);
    glVertex2i(133 + offsetX, 75 + offsetY);
    glVertex2i(133 + offsetX, 165 + offsetY);
    glVertex2i(120 + offsetX, 160 + offsetY);
    glEnd();

    // Main body of the barricade
    glColor3ub(255, 165, 0);  // orange
    glBegin(GL_QUADS);
    glVertex2i(50 + offsetX, 100 + offsetY);
    glVertex2i(150 + offsetX, 140 + offsetY);
    glColor3ub(255, 135, 0);
    glVertex2i(150 + offsetX, 160 + offsetY);
    glVertex2i(50 + offsetX, 120 + offsetY);
    glEnd();

    glColor3ub(255, 165, 0);
    glBegin(GL_QUADS);
    glVertex2i(50 + offsetX, 70 + offsetY);
    glVertex2i(150 + offsetX, 110 + offsetY);
    glColor3ub(255, 135, 0);
    glVertex2i(150 + offsetX, 130 + offsetY);
    glVertex2i(50 + offsetX, 90 + offsetY);
    glEnd();
}

//Rickshaw
void drawRickshaw(int offsetX, int offsetY) {

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(offsetX + 200, offsetY + 200);
	glVertex2i(offsetX + 260, offsetY + 200);
	glVertex2i(offsetX + 260, offsetY + 202);
	glVertex2i(offsetX + 200, offsetY + 202);

	glVertex2i(offsetX + 260, offsetY + 210);
	glVertex2i(offsetX + 265, offsetY + 210);
	glVertex2i(offsetX + 265, offsetY + 170);
	glVertex2i(offsetX + 270, offsetY + 170);

	glVertex2i(offsetX + 200, offsetY + 205);
	glVertex2i(offsetX + 260, offsetY + 205);
	glVertex2i(offsetX + 260, offsetY + 207);
	glVertex2i(offsetX + 200, offsetY + 207);

	glVertex2i(offsetX + 200, offsetY + 200);
	glVertex2i(offsetX + 200, offsetY + 203);
	glVertex2i(offsetX + 230, offsetY + 170);
	glVertex2i(offsetX + 233, offsetY + 173);

	glVertex2i(offsetX + 260, offsetY + 200);
	glVertex2i(offsetX + 260, offsetY + 203);
	glVertex2i(offsetX + 230, offsetY + 170);
	glVertex2i(offsetX + 233, offsetY + 173);

	glVertex2i(offsetX + 200, offsetY + 213);
	glVertex2i(offsetX + 205, offsetY + 213);
	glVertex2i(offsetX + 195, offsetY + 170);
	glVertex2i(offsetX + 200, offsetY + 173);

	glVertex2i(offsetX + 250, offsetY + 170);
	glVertex2i(offsetX + 230, offsetY + 175);
	glVertex2i(offsetX + 280, offsetY + 175);
	glVertex2i(offsetX + 280, offsetY + 170);

	glVertex2i(offsetX + 250, offsetY + 170);
	glVertex2i(offsetX + 230, offsetY + 180);
	glVertex2i(offsetX + 250, offsetY + 180);
	glVertex2i(offsetX + 230, offsetY + 170);

	glVertex2i(offsetX + 200, offsetY + 213);
	glVertex2i(offsetX + 215, offsetY + 213);
	glVertex2i(offsetX + 200, offsetY + 216);
	glVertex2i(offsetX + 215, offsetY + 216);

	glColor3f(0.0, 330.0, 0.0);
	glVertex2i(offsetX + 210, offsetY + 213);
	glVertex2i(offsetX + 240, offsetY + 216);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.50);
	glVertex2i(offsetX + 267, offsetY + 192);
	glVertex2i(offsetX + 292, offsetY + 192);
	glVertex2i(offsetX + 302, offsetY + 202);
	glVertex2i(offsetX + 302, offsetY + 212);
	glVertex2i(offsetX + 292, offsetY + 212);
	glVertex2i(offsetX + 292, offsetY + 202);
	glVertex2i(offsetX + 267, offsetY + 202);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.50, 0.0, 0.0);
	glVertex2i(offsetX + 287, offsetY + 227);
	glVertex2i(offsetX + 302, offsetY + 227);
	glVertex2i(offsetX + 307, offsetY + 255);
	glVertex2i(offsetX + 290, offsetY + 255);
	glVertex2i(offsetX + 275, offsetY + 260);
	glVertex2i(offsetX + 275, offsetY + 255);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.0, 0.90, 0.0);
	glVertex2i(offsetX + 292, offsetY + 227);
	glVertex2i(offsetX + 294, offsetY + 227);
	glVertex2i(offsetX + 292, offsetY + 210);
	glVertex2i(offsetX + 294, offsetY + 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.90, 0.0);
	glVertex2i(offsetX + 288, offsetY + 227);
	glVertex2i(offsetX + 290, offsetY + 227);
	glVertex2i(offsetX + 292, offsetY + 210);
	glVertex2i(offsetX + 294, offsetY + 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.90, 0.0);
	glVertex2i(offsetX + 296, offsetY + 227);
	glVertex2i(offsetX + 300, offsetY + 227);
	glVertex2i(offsetX + 292, offsetY + 210);
	glVertex2i(offsetX + 294, offsetY + 210);
	glEnd();

	//wheel
	glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    int numSegments = 50;
    float radius = 25.0; // Radius of the wheel
    float cx = offsetX + 200; // Center X of the wheel
    float cy = offsetY + 165; // Center Y of the wheel

    for (int i = 0; i < numSegments; i++) {
        float angle = 2 * M_PI * i / numSegments;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 23, 22);
    float cx2 = offsetX + 285;
    float cy2 = offsetY + 165;

    for (int i = 0; i < numSegments; i++) {
        float angle = 2 * M_PI * i / numSegments;
        float x = cx2 + radius * cos(angle);
        float y = cy2 + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Draw Tree
void drawTreeType1(int offsetX, int offsetY) {

    glBegin(GL_QUADS);
    glColor3ub(80, 49, 30);  // Light brown color
    glVertex2i(457 + offsetX, 200 + offsetY);
    glVertex2i(457 + offsetX, 225 + offsetY);
    glColor3ub(100, 49, 30);  // Dark brown color
    glVertex2i(442 + offsetX, 225 + offsetY);
    glVertex2i(442 + offsetX, 200 + offsetY);
    glEnd();

    glBegin(GL_TRIANGLES); // Tree bot
    glColor3ub(30, 75, 40);
    glVertex2i(480 + offsetX, 225 + offsetY);  // bottom right
    glVertex2i(450 + offsetX, 260 + offsetY);  // top
    glVertex2i(420 + offsetX, 225 + offsetY);  // bottom left
    glEnd();

    glBegin(GL_TRIANGLES); // Tree mid1
    glColor3ub(30, 95, 40);
    glVertex2i(480 + offsetX, 240 + offsetY);  // bottom right
    glVertex2i(450 + offsetX, 270 + offsetY);  // top
    glVertex2i(420 + offsetX, 240 + offsetY);  // bottom left
    glEnd();

    glBegin(GL_TRIANGLES); // Tree mid2
    glColor3ub(30, 115, 40);
    glVertex2i(475 + offsetX, 255 + offsetY);  // bottom right
    glVertex2i(450 + offsetX, 280 + offsetY);  // top
    glVertex2i(425 + offsetX, 255 + offsetY);  // bottom left
    glEnd();

    glBegin(GL_TRIANGLES); // Tree  top
    glColor3ub(30, 135, 40);
    glVertex2i(470 + offsetX, 270 + offsetY);  // bottom right
    glVertex2i(450 + offsetX, 290 + offsetY);  // top
    glVertex2i(430 + offsetX, 270 + offsetY);  // bottom left
    glEnd();
}

//draw House
void drawHouseType1(int offsetX, int offsetY, unsigned char r, unsigned char g, unsigned char b) {
    // Draw Building Body
    glColor3ub(r, g, b);
    //glColor3ub(80, 49, 30);  // Dark brown building
    glBegin(GL_QUADS);
    glVertex2i(400 + offsetX, 200 + offsetY);  // Bottom-left
    glVertex2i(516 + offsetX, 200 + offsetY);  // Bottom-right
    glVertex2i(516 + offsetX, 400 + offsetY);  // Top-right
    glVertex2i(400 + offsetX, 400 + offsetY);  // Top-left
    glEnd();

    // Windows
    //glColor3ub(173, 216, 230);
    int windowWidth = 25;
    int windowHeight = 30;
    int gapX = 10; // Horizontal gap between windows
    int gapY = 15; // Vertical gap between windows
    int startX = 410 + offsetX; // Initial X position for first window
    int startY = 360 + offsetY; // Initial Y position for first row of windows

    for (int row = 0; row < 4; row++) {  // 3 Rows
        for (int col = 0; col < 3; col++) {  // 3 Columns
            int x = startX + col * (windowWidth + gapX);
            int y = startY - row * (windowHeight + gapY);

            glBegin(GL_QUADS);
            glColor3ub(0, 102, 204);
            glVertex2i(x, y);
            glVertex2i(x + windowWidth, y);
            glColor3ub(135, 206, 250);
            glVertex2i(x + windowWidth, y - windowHeight);
            glVertex2i(x, y - windowHeight);
            glEnd();
        }
    }
}

//draw Man
void drawMan(int x, int y, float angle) {
    glPushMatrix();  // Save current transformation state

    // Move the origin of the drawing to the center of the man for rotation
    glTranslatef(x + 20, y + 25, 0);  // Translate to the center of the man
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate around the z-axis (in 2D)

    glTranslatef(-(x + 20), -(y + 25), 0);  // Translate back to the original position

    // Face (Light Brown Square)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.52, 0.25);
    glVertex2i(x + 10, y + 30);
    glVertex2i(x + 30, y + 30);
    glVertex2i(x + 30, y + 50);
    glVertex2i(x + 10, y + 50);
    glEnd();

    // Eyes (Black Rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 10, y + 45);
    glVertex2i(x + 30, y + 45);
    glVertex2i(x + 30, y + 55);
    glVertex2i(x + 10, y + 55);
    glEnd();

    // Hand (Rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.52, 0.25);
    glVertex2i(x - 2, y + 10);   // Bottom Left
    glVertex2i(x + 35, y + 10);  // Bottom Right
    glVertex2i(x + 35, y + 30);  // Top Right
    glVertex2i(x - 2, y + 30);  // Top Left
    glEnd();

    // Body (Dark Green)
    glBegin(GL_QUADS);
    glColor3ub(200, 205, 200);
    glVertex2i(x + 5, y + 8);
    glVertex2i(x + 35, y + 8);
    glVertex2i(x + 35, y + 30);
    glVertex2i(x + 5, y + 30);
    glEnd();

    // Legs (Green)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 8, y - 8);
    glVertex2i(x + 18, y - 8);
    glVertex2i(x + 18, y + 10);
    glVertex2i(x + 8, y + 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x + 22, y - 8);
    glVertex2i(x + 32, y - 8);
    glVertex2i(x + 32, y + 10);
    glVertex2i(x + 22, y + 10);
    glEnd();

    glPopMatrix();  // Restore the transformation state
}

void drawLamppost(int x, int y) {
    // Lamppost Pole
    glBegin(GL_QUADS);
    glColor3ub(17, 15, 15);
    glVertex2i(x - 5, y + 50);      // Bottom-left
    glVertex2i(x + 5, y + 50);      // Bottom-right
    glVertex2i(x + 1, y + 100); // Top-right
    glVertex2i(x - 1, y + 100); // Top-left
    glEnd();

    // Lamp (Circle)
    glColor3f(1.0, 1.0, 0.0); // Yellow color for light
    float radius = 7.0f;
    int segments = 30; // Number of segments for the circle

    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(x, y + 100);
    for (int i = 0; i <= segments; i++) {
        float angle = (2 * 3.14159265359 * i) / segments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2i(x + dx, y + 100 + dy);
    }
    glEnd();
}

void drawBlood(int x, int y, float radius1, float radius2) {
    glColor3f(1.0, 0.0, 0.0);  // Bright red color

    int segments = 30;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(x, y); // Center of the blood drop

    // Draw the circle (blood drop)
    for (int i = 0; i <= segments; i++) {
        float angle = (2 * 3.14159265359 * i) / segments;
        float dx = radius1 * cos(angle);
        float dy = radius2 * sin(angle);
        glVertex2i(x + dx, y + dy); // Adjusted for center
    }
    glEnd();
}

void drawFire(int x, int y) {
    if (showFire) {
        glColor3f(1.0, 0.27, 0.0);  // Fire red color

        // Draw the first triangle
        glBegin(GL_TRIANGLES);
        glVertex2i(x, y);
        glVertex2i(x + 20, y);
        glVertex2i(x + 10, y + 20);
        glEnd();

        // Draw the second triangle
        glBegin(GL_TRIANGLES);
        glVertex2i(x + 10, y);
        glVertex2i(x + 30, y);
        glVertex2i(x + 20, y + 20);
        glEnd();

        // Draw the third triangle
        glBegin(GL_TRIANGLES);
        glVertex2i(x + 20, y);
        glVertex2i(x + 40, y);
        glVertex2i(x + 30, y + 20);
        glEnd();

        // Draw the fourth triangle
        glBegin(GL_TRIANGLES);
        glVertex2i(x + 30, y);
        glVertex2i(x + 50, y);
        glVertex2i(x + 40, y + 20);
        glEnd();
    }
}

void toggleFire(int value) {
    // Toggle the fire visibility
    showFire = !showFire;

    // Call this function every "flashSpeed" milliseconds to toggle visibility
    glutPostRedisplay();  // Redraw the screen
    glutTimerFunc(flashSpeedFire, toggleFire, 0);  // Repeat the timer
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with the sky color

    // Draw the clouds
    drawCloud(cloud1Pos, 450);
    drawCloud(cloud2Pos, 520);
    drawCloud(cloud3Pos, 500);
    drawCloud(cloud4Pos, 500);
    drawCloud(cloud5Pos, 500);

    //house
    drawHouseType1(-100, -50, 230, 230, 250);
    drawHouseType1(-250, -10, 178, 34, 34);
    drawHouseType1(-350, -20, 169, 169, 169);
    drawHouseType1(-450, -50, 80, 49, 30);
    drawHouseType1(-180, -70, 245, 245, 220);

    drawHouseType1(300, 10, 80, 49, 30);
    drawHouseType1(100, -20, 169, 169, 169);
    drawHouseType1(0, 10, 30, 49, 80);

    drawTreeType1(-70, -5);
    drawTreeType1(70, -5);
    drawTreeType1(100, -5);
    drawHouseType1(400, 0, 30, 49, 80);
    drawHouseType1(200, -100, 245, 245, 220);
    drawHouseType1(500, -30, 128, 128, 0);


    drawRoad();
    // Draw the road
    drawFence(0, -70);

    drawTreeType1(440, -5);
    drawTreeType1(360, -5);
    drawTreeType1(300, -5);
    drawTreeType1(330, -5);
    drawTreeType1(-350, -5);
    drawTreeType1(-400, -5);
    drawTreeType1(-200, -5);
    drawTreeType1(-250, -5);

    drawLamppost(350,140);
    drawLamppost(50,140);
    drawLamppost(650,140);
    drawLamppost(950,140);

    drawTent(-600, -330);
    drawTent(-720, -330);

    drawBlood(530, 160, 20.0f, 15.0f);
    //draw man (Rickshaw)
    drawMan(500, 150, -75.0f);
    drawBlood(520, 170, 5.0f, 5.0f);
    //draw fire
    drawFire(635, 130);
    drawRickshaw(400, -20);
    //draw fire
    drawFire(660, 115);

    // Draw the tank
    drawTank(tankPos, -190);


    //draw man (Rickshaw)
    //drawMan(550, 150, 65.0f);

    //draw army
    drawArmy(100, 100);
    drawArmy(85, 80);
    drawArmy(70, 65);
    drawArmy(85, 40);
    drawArmy(65, 20);

    drawBarricade(200, -50);
    drawBarricade2(320, -50);

    // Draw raindrops
    if (isRaining) {
        drawRaindrops();
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A') {
        tankSpeed = max(0.0f, tankSpeed - 0.01f); // Decrease tank speed,
    } else if (key == 'd' || key == 'D') {
        tankSpeed += 0.01f; // Increase tank speed
    }

    if (key == 'r' || key == 'R') {
        isRaining = !isRaining; // Toggle rain animation on or off
        if (isRaining)
        {
            skyColor[0] = 0.6f;
            skyColor[1] = 0.6f;
            skyColor[2] = 0.6f;
            glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]);
        }
        else
        {
             // Change background color back to light blue
            skyColor[0] = 0.53f;
            skyColor[1] = 0.81f;
            skyColor[2] = 0.98f;
            glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]);
        }
    }

    if (key == 'n' || key == 'N') {
        // Change background color to black
        skyColor[0] = 0.1529f;  //39
        skyColor[1] = 0.2471f;  // 63
        skyColor[2] = 0.3765f; // 96
        glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]);

    }
    else if (key == 'b' || key == 'B') {
        // Change background color back to light blue
        skyColor[0] = 0.53f;
        skyColor[1] = 0.81f;
        skyColor[2] = 0.98f;
        glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]);
    }
}

int main(int argc, char** argv)
{
    cout << endl << "July Revolution Rendition: Echos of freedom " << endl;
    cout << endl << "=============================================" << endl << endl;
    cout << "Keybinds:" << endl << endl ;
    cout << "A = Decrease the Tank speed" << endl ;
    cout << "D = Increase the Tank speed" << endl ;
    cout << "N = Switch to night sky" << endl ;
    cout << "B = Switch to day sky" << endl ;
    cout << "R = Toggle between rainy and clear sky" << endl ;
    cout << endl << "=============================================" << endl << endl;
    cout << "COMPUTER GRAPHICS [G]" << endl ;
    cout << "Fall 2024-2025" << endl;
    cout << "Course Instructor: Dipta Justin Gomes" << endl << endl;
    cout << "Submitted by:" << endl << endl;
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
    glutKeyboardFunc(keyboard);
    glutTimerFunc(flashSpeedFire, toggleFire, 0);
    glutMainLoop();
    return 0;
}
