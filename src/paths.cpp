#include "paths.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

void linePath(int time) {
    float current = time % 100;
    glTranslatef(0.0f, 0.0f, ((float)current/5) * 1.0f);
}

void drawLinePath() {
    glColor3f(0, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex3f(0, 0.2, 0);
    glVertex3f(0, 0.2, 20);
    glEnd();
}

void circlePath(int time, struct rotation_s* rotation) {
    float current = (float)time / 10;
    glTranslatef(cos(current) * 10.0f, 0.0f, sin(current) * 10.0f);
    rotation->y = 2 * -current;
}

void drawCirclePath() {
	glColor3f(0, 0.5, 0.5);
	glRotatef(90, 1.0, 0, 0);
	drawCircle(0, 0.1, 0, 20, 19);
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
	GLint numberOfVertices = numberOfSides + 1;

	GLfloat doublePi = 2.0f * 3.14159;

	GLfloat circleVerticesX[20];
	GLfloat circleVerticesY[20];
	GLfloat circleVerticesZ[20];

	for (int i = 0; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[20 * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}