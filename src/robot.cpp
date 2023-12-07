#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include "robot.hpp"
#include "texturedPrimitives.hpp"
#include "data.h"
#include <math.h>

void renderRobotSolid(struct rotation_s* rotation, struct displaySettings_s* displaySettings, GLuint *textures) {
    // Head
    glPushMatrix();
    glTranslatef(0.0, 7.5, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    eglSphere(40, textures[3]);

    // Gundam crown 
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(80, 0, 0, 1);
        glScalef(3.0, 0.25, 0.25);
        glutSolidCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(30, 0, 0, 1);
        glScalef(2.0, 0.25, 0.25);
        glutSolidCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(-80, 0, 0, 1);
        glScalef(3.0, 0.25, 0.25);
        glutSolidCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(-30, 0, 0, 1);
        glScalef(2.0, 0.25, 0.25);
        glutSolidCone(2, 3, 10, 10);
        glPopMatrix();
    }

    glPopMatrix();

    // Torso
    glPushMatrix();
    glScalef(5.0, 10.0, 2.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
	eglCube(1, 1, 1, textures[3]);

     //Body antennae 
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glRotatef(30, 1, 0, 1);
        glScalef(0.5, 0.12, 0.12);
        eglCube(2, 2, 2, textures[3]);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.5, 0.5, 0.0);
        glRotatef(-30, 1, 0, 1);
        glScalef(0.5, 0.12, 0.12);
        eglCube(2, 2, 2, textures[3]);
        glPopMatrix();
    }
    glPopMatrix();

    // Left thigh
    glPushMatrix();
    glScalef(3.0, 10.0, 2.0);
    glTranslatef(1.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_hip, 1, 0, 0);
	eglCube(1, 1, 1, textures[3]);

    // Left lower leg
    glTranslatef(0.0, -1.0, 0.0);
    glScalef(1, 1, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_knee, 1, 0, 0);
	eglCube(1, 1, 1, textures[3]);
    glPopMatrix();

    // Right thigh
    glPushMatrix();
    glScalef(3.0, 10.0, 2.0);
    glTranslatef(-1.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->r_hip, 1, 0, 0);
	eglCube(1, 1, 1, textures[3]);
    
    // Right lower leg
    glTranslatef(0.0, -1.0, 0.0);
    glScalef(1, 1, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->r_knee, 1, 0, 0);
	eglCube(1, 1, 1, textures[3]);
    glPopMatrix();

    // Left upper arm
    glPushMatrix();
    glScalef(6.0, 2.0, 2.0);
    glTranslatef(0.8, 1.0, 0.0);
    glRotatef(-45, 0, 0, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_shoulder, 0, 1, 0);
	eglCube(1, 1, 1, textures[3]);

    // Left lower arm
    glScalef(1, 1, 1);
    glTranslatef(1, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_elbow, 0, 0, 1);
	eglCube(1, 1, 1, textures[3]);

    //Gundam shield
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glScalef(1, 4, 1);
        eglCube(1, 1, 1, textures[3]);

        glPushMatrix();
        glScalef(0.8, 0.75, 0.8);
        glTranslatef(0, 1, 0);
        eglCube(1, 1, 1, textures[3]);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.4, 1, 0.4);
        glTranslatef(0.6, -1, 0);
        eglCube(1, 1, 1, textures[3]);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.4, 1, 0.4);
        glTranslatef(-0.6, -1, 0);
        eglCube(1, 1, 1, textures[3]);
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();

    // Right upper arm
    glPushMatrix();
    glScalef(6.0, 2.0, 2.0);
    glTranslatef(-0.8, 1.0, 0.0);
    glRotatef(45, 0, 0, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(-rotation->r_shoulder, 0, 1, 0);
	eglCube(1, 1, 1, textures[3]);

    // Right lower arm
    //glScalef(4.0, 2.0, 2.0);
    glScalef(1, 1, 1);
    glTranslatef(-1, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(-rotation->r_elbow, 0, 0, 1);
	eglCube(1, 1, 1, textures[3]);
    glPopMatrix();
}

void renderRobotWire(struct rotation_s* rotation, struct displaySettings_s* displaySettings) {
    // Head
    glPushMatrix();
    glTranslatef(0.0, 7.5, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glutWireSphere(2.5, 25, 25);

    // Gundam crown 
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(80, 0, 0, 1);
        glScalef(3.0, 0.25, 0.25);
        glutWireCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(30, 0, 0, 1);
        glScalef(2.0, 0.25, 0.25);
        glutWireCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(-80, 0, 0, 1);
        glScalef(3.0, 0.25, 0.25);
        glutWireCone(2, 3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(-30, 0, 0, 1);
        glScalef(2.0, 0.25, 0.25);
        glutWireCone(2, 3, 10, 10);
        glPopMatrix();
    }

    glPopMatrix();


    // Torso
    glPushMatrix();
    glScalef(5.0, 10.0, 2.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
	glutWireCube(1);
    //Body antennae 
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glRotatef(30, 1, 0, 1);
        glScalef(0.5, 0.12, 0.12);
        glutWireCube(2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.5, 0.5, 0.0);
        glRotatef(-30, 1, 0, 1);
        glScalef(0.5, 0.12, 0.12);
        glutWireCube(2);
        glPopMatrix();
    }
    glPopMatrix();

    // Left thigh
    glPushMatrix();
    glScalef(3.0, 10.0, 2.0);
    glTranslatef(1.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_hip, 1, 0, 0);
	glutWireCube(1);

    // Left lower leg
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_knee, 1, 0, 0);
	glutWireCube(1);
    glPopMatrix();

    // Right thigh
    glPushMatrix();
    glScalef(3.0, 10.0, 2.0);
    glTranslatef(-1.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->r_hip, 1, 0, 0);
	glutWireCube(1);
    
    // Right lower leg
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->r_knee, 1, 0, 0);
	glutWireCube(1);
    glPopMatrix();

    // Left upper arm
    glPushMatrix();
    glScalef(6.0, 2.0, 2.0);
    glTranslatef(0.8, 1.0, 0.0);
    glRotatef(-45, 0, 0, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_shoulder, 0, 1, 0);
	glutWireCube(1);

    // Left lower arm
    //glScalef(4.0, 2.0, 2.0);
    glTranslatef(1, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(rotation->l_elbow, 0, 0, 1);
	glutWireCube(1);
    //Gundam shield
    if (displaySettings->GUNDAM == true) {
        glPushMatrix();
        glScalef(1, 4, 1);
        glutWireCube(1);

        glPushMatrix();
        glScalef(0.8, 0.75, 0.8);
        glTranslatef(0, 1, 0);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.4, 1, 0.4);
        glTranslatef(0.6, -1, 0);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.4, 1, 0.4);
        glTranslatef(-0.6, -1, 0);
        glutWireCube(1);
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();

    // Right upper arm
    glPushMatrix();
    glScalef(6.0, 2.0, 2.0);
    glTranslatef(-0.8, 1.0, 0.0);
    glRotatef(45, 0, 0, 1);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(-rotation->r_shoulder, 0, 1, 0);
	glutWireCube(1);

    // Right lower arm
    //glScalef(4.0, 2.0, 2.0);
    glTranslatef(-1, 0.0, 0.0);
    glRotatef(rotation->x, 1, 0, 0);
    glRotatef(rotation->y, 0, 1, 0);
    glRotatef(rotation->z, 0, 0, 1);
    glRotatef(-rotation->r_elbow, 0, 0, 1);
	glutWireCube(1);
    glPopMatrix();
}

void displayAxes() {
    // X axis
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(1000, 0, 0);
    glEnd();

    // Y axis
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1000, 0);
    glEnd();

    // Z axis
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1000);
    glEnd();

	glRotatef(0, 0, 0, 0);
}

void drawCamera(vec3<float> pos, vec3<float> facing) {
    glPushMatrix();

    glColor3f(1.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glutWireCube(1);
    glPopMatrix();

    glBegin(GL_LINES);
    glVertex3f(pos.x, pos.y, pos.z);
    glVertex3f(facing.x, facing.y, facing.z);
    glEnd();

    glPopMatrix();
}

void drawTree(GLuint leaf, GLuint bark) {
    glPushMatrix();

    eglCube(5, 5, 20, bark);

    glTranslatef(0, 20, 0);
    eglCube(10, 10, 20, leaf);
    glTranslatef(0, 20, 0);
    eglCube(5, 5, 20, leaf);

    glPopMatrix();
}