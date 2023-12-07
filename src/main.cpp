// Eva Powlison
// Computer Graphics class
// Fall 2023

#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/freeglut_std.h>
//#include <GL/freeglut_ext.h>
//#include <GL/glut.h>
//#include <GL/glext.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "robot.hpp" // Contains functions for drawing various objects, mainly the robot
#include "data.h" // Contains data shared between files 
#include "camera.hpp" // Camera class
#include "paths.h" // Path data
#include "load_texture.h"
#include "texturedPrimitives.hpp"

// Definitions for structs are found in data.h 
displaySettings_t displaySettings = {true, false, true, true, true, true, true, false, true, true, true, 1.0, 0.0, 0.0}; //Everything except Gundam enabled by default
rotation_t rotation = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
mouse_s mouse = {0, 0, 0, 0, true, 0.20};

unsigned int textures[5];

camera innerCam;
camera outerCam;
camera *activeCam;

int windowWidth = 1080;
int windowHeight = 720;

int aniSeconds = 0;
int aniState = 0;
int movementTime = 0;

void animation() {
	if(displaySettings.PLAY_ANIMATION) {
		if (aniState == 0) {
			rotation.r_shoulder = aniSeconds;
			rotation.r_hip = aniSeconds;
			rotation.l_shoulder = -aniSeconds;
			rotation.l_hip = -aniSeconds;
			rotation.l_elbow = aniSeconds;
			rotation.l_knee = aniSeconds;
			rotation.r_elbow = -aniSeconds;
			rotation.r_knee = -aniSeconds;
		} else {
			rotation.r_shoulder = -aniSeconds;
			rotation.r_hip = -aniSeconds;
			rotation.l_shoulder = aniSeconds;
			rotation.l_hip = aniSeconds;

			rotation.l_elbow = -aniSeconds;
			rotation.l_knee = -aniSeconds;
			rotation.r_elbow = aniSeconds;
			rotation.r_knee = aniSeconds;
		}
	}
}

void timer(int v) {
	if (displaySettings.PLAY_ANIMATION) {
		if(aniSeconds <= 60 && aniState == 0) {
			rotation.r_shoulder += 1;
			rotation.r_hip += 1;
			rotation.l_shoulder -= 1;
			rotation.l_hip -= 1;
			rotation.l_elbow += 1;
			rotation.l_knee += 1;
			rotation.r_elbow -= 1;
			rotation.r_knee -= 1;

			++aniSeconds;
			if (aniSeconds >= 60) aniState = 1;
		} else {
			rotation.r_shoulder -= 1;
			rotation.r_hip -= 1;
			rotation.l_shoulder += 1;
			rotation.l_hip += 1;

			rotation.l_elbow -= 1;
			rotation.l_knee -= 1;
			rotation.r_elbow += 1;
			rotation.r_knee += 1;

			--aniSeconds;
			if(aniSeconds <= -60) aniState = 0;
		}
	}

	++movementTime;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
}

void drawScene() {

	glEnable(GL_TEXTURE_2D);
	if (displaySettings.DISPLAY_SOLID) eglCube(500, 500, 500, textures[4]); // skybox
	glDisable(GL_TEXTURE_2D);

	// Draw floor
	if(displaySettings.DISPLAY_SOLID == true) {
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, textures[0]); // grass texture
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-100.0f, -0.5f, -100.f);
		glTexCoord2f(0.0, 4.0);
		glVertex3f(-100.0f,-0.5f, 100.f);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(100.0f, -0.5f, 100.f);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(100.0f, -0.5f, -100.f);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	} else {
		//glPolygonMode( GL_FRONT, GL_LINE );
		glPushMatrix();
		glColor3f(0.8,0.8,0.8);
		for(int dir = 0; dir < 2; dir++)
		{
			for(int i = -100; i < 100; i++)
			{
				glBegin(GL_LINE_STRIP);
				for(int j = -100; j < 100; j++)
					glVertex3f(dir<1?i:j, -0.73f, dir<1?j:i);
				glEnd();
			}
		}

		glPopMatrix();
		//glPolygonMode( GL_FRONT, GL_FILL );
	}
	
	// Forest
	for(float i = -5; i < 5; i++) {
		for(float j = -5; j < 5; j++) {
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(i * 20 + (i + j)/(j - i), 5, j * 20 + (i - j) * (i / j));
			drawTree(textures[1], textures[2]);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
	}

	glPushMatrix();
	//Movement
	if (displaySettings.PLAY_ANIMATION) {
		linePath(movementTime);
	}

	//Display robot
	glTranslatef(0, 25, 0);
	glEnable(GL_TEXTURE_2D);
	if (displaySettings.DISPLAY_SOLID) renderRobotSolid(&rotation, &displaySettings, textures);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_TEXTURE_2D);
	if (displaySettings.DISPLAY_WIRE) renderRobotWire(&rotation, &displaySettings);
	glPopMatrix();

	if(displaySettings.DISPLAY_AXIS) displayAxes();

}

void display() {
	// Outer cam
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float borderWidth = 3; 
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);

    vec3<float> camPos = outerCam.getPos();
    vec3<float> camFacing = outerCam.getForward();
    camFacing = camPos + camFacing;
    vec3<float> camUp = outerCam.getUp();
    gluLookAt(camPos.x, camPos.y, camPos.z, 
                    camFacing.x, camFacing.y, camFacing.z, 
                    camUp.x, camUp.y, camUp.z);

	camPos = innerCam.getPos();
    camFacing = innerCam.getForward();
    camFacing = camPos + camFacing;

	drawCamera(camPos, camFacing); // Camera bee

	drawScene();

	glDisable(GL_TEXTURE_2D);

// This was lifted directly from the thing we were supposed to steal it from

///     draw border and background for preview box in upper corner  //////////////////////

    //next, do the code for the inner camera, which only sets in the top-right
    //corner!
    glDisable(GL_DEPTH_TEST);

    //step 1: set the projection matrix using gluOrtho2D -- but save it first!
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);

    //step 2: clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //step 3: set the viewport matrix a little larger than needed...
    glViewport(2*windowWidth/3.0-borderWidth, 2*windowHeight/3.0-borderWidth, 
                windowWidth/3.0+borderWidth, windowHeight/3.0+borderWidth);
    //step 3a: and fill it with a white rectangle!
    if(*&activeCam == &outerCam) // Compare memory addresses to see if the cameras are the same
        glColor3f(1,1,1);
    else
        glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0,0); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,0);
    glEnd();

    //step 4: trim the viewport window to the size we want it...
    glViewport(2*windowWidth/3.0, 2*windowHeight/3.0, 
                windowWidth/3.0, windowHeight/3.0);
    //step 4a: and color it black! the padding we gave it before is now a border.
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0,0); glVertex2f(0,1); glVertex2f(1,1); glVertex2f(1,0);
    glEnd();

    //before rendering the scene in the corner, pop the old projection matrix back
    //and re-enable lighting!
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

	// Inner cam
	glViewport(2*windowWidth/3.0, 2*windowHeight/3.0, windowWidth/3.0, windowHeight/3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    camUp = innerCam.getUp();
    gluLookAt(camPos.x, camPos.y, camPos.z, 
                    camFacing.x, camFacing.y, camFacing.z, 
                    camUp.x, camUp.y, camUp.z);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	drawScene();

	glFlush();
	glutSwapBuffers();
}

void resizeWindow(int w, int h) {
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
	
	glutPostRedisplay();
}

void init(void) {
	glClearColor(0, 0, 0, 1.0);
	glColor3f(1, 1, 1);

	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-2, 2, -2, 2, 1, 1000);
	glMatrixMode(GL_MODELVIEW); 

	glLoadIdentity();

	activeCam = &innerCam;
	innerCam.setPos(vec3<float>(0, 5, 0));
	outerCam.setPos(vec3<float>(-75, 75, 10));
	//outerCam.setForward(vec3<float>(0, 0, 0));

	textures[0] = eglLoadBMP("textures/grass.bmp");
	textures[1] = eglLoadBMP("textures/leaf.bmp");
	textures[2] = eglLoadBMP("textures/bark.bmp");
	textures[3] = eglLoadBMP("textures/metal.bmp");
	textures[4] = eglLoadBMP("textures/stars.bmp");

	glEnable(GL_DEPTH_TEST);
}

void procKeys(unsigned char key, int x, int y) {
    switch(key) {
		case '1':
			if (displaySettings.DISPLAY_SOLID == true) {
				displaySettings.DISPLAY_SOLID = false;
				displaySettings.DISPLAY_WIRE = true;
			} else {
				displaySettings.DISPLAY_SOLID = true;
				displaySettings.DISPLAY_WIRE = false;
			}
			break;
		case '2':
			if (displaySettings.DISPLAY_AXIS == true) displaySettings.DISPLAY_AXIS = false;
			else displaySettings.DISPLAY_AXIS = true;
			break;
		case 'a':
			if (displaySettings.PLAY_ANIMATION == true) displaySettings.PLAY_ANIMATION = false;
			else displaySettings.PLAY_ANIMATION = true;
        case 'i':
            activeCam = &innerCam;
            break;
        case 'o':
            activeCam = &outerCam;
            break;
        case 'm':
            if (mouse.capture == true) mouse.capture = false;
            else mouse.capture = true;
            break;
		case 'r':
			activeCam->setPos(vec3<float>(0, 0, 0));
			break;
        case 27:
            printf("Quitting...\n");
            exit(0);
            break; 
        case 32: // Spacebar
            activeCam->keyboardMovement("up");
            break;
    }
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            activeCam->keyboardMovement("forward");
            break;
        case GLUT_KEY_DOWN:
            activeCam->keyboardMovement("back");
            break;
        case GLUT_KEY_CTRL_L:
            activeCam->keyboardMovement("down");
            break;
        case GLUT_KEY_LEFT:
            activeCam->keyboardMovement("left");
            break;
        case GLUT_KEY_RIGHT:
            activeCam->keyboardMovement("right");
            break;
		case GLUT_KEY_F8:
			if(displaySettings.GUNDAM == false) displaySettings.GUNDAM = true;
			else displaySettings.GUNDAM = false;
    }

    glutPostRedisplay();
}

void procMouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) mouse.leftMouse = state;
    if(button == GLUT_RIGHT_BUTTON) mouse.rightMouse = state;

    mouse.x = x;
    mouse.y = y;
}

void mouseMotion(int x, int y) {
    //if(mouse.leftMouse == GLUT_DOWN) {

        float dx = (x - mouse.x) * mouse.sensitivity;
        float dy = (y - mouse.y) * mouse.sensitivity;
        
        activeCam->mouseMovement(dx, dy);

        mouse.x = x;
        mouse.y = y;

        if (mouse.capture) {
            glutSetCursor(GLUT_CURSOR_NONE);
            if (x > windowWidth - 5 | x < 5 | y > windowHeight - 5 | y < 5) {
                    glutWarpPointer(windowWidth / 2, windowHeight / 2);
                    mouse.x = windowWidth / 2;
                    mouse.y = windowHeight / 2;
            }
        } else {
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }

        glutPostRedisplay();
    //}
}
void printInstructions() {
	printf("========================================\n");
	printf("KEYBOARD CONTROLS\n");
    printf("Use the arrow keys to move the inner camera\n");
    printf("space - move camera up\n");
    printf("L-CTRL - move camera down\n");
    printf("1 - toggle wire/solid display\n");
    printf("2 - toggle basis axes display\n");
    printf("a - toggle robot animation\n");
    printf("i - select inner camera\n");
    printf("o - select outer camera\n");
    printf("m - toggle mouse capture\n");
	printf("r - reset position of camera at origin\n");
	printf("F8 - enable Gundam Mode\n");
	printf("ESC - quit program\n");
	printf("========================================\n");

}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);

	int x = 200;
	int y = 100;
	glutInitWindowPosition(x, y);

	int win = glutCreateWindow("Graphics Final");
	
	printInstructions();

	init();

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(display);
	glutKeyboardFunc(procKeys);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(procMouse);
	glutPassiveMotionFunc(mouseMotion);
	glutMotionFunc(mouseMotion);

	glutMainLoop();

	return 0;
}
