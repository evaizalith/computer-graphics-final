#include "texturedPrimitives.hpp"
#include <math.h>
#include <GL/gl.h>

typedef struct
{
	int X;
	int Y;
	int Z;
	double U;
	double V;
}VERTICES;

const double PI = 3.1415926535897;
const int space = 11;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];

void quadBox(float size, GLenum type) {
    	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void eglCube(float l, float w, float h, unsigned int texture_id) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glScalef(w, h, l);

    quadBox(1, GL_QUADS);

    glPopMatrix();
}

void CreateSphere(double R, double H, double K, double Z) {
	int n;
	double a;
	double b;
	n = 0;
	for (b = 0; b <= 90 - space; b += space) {

		for (a = 0; a <= 360 - space; a += space)
		{
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a) / 360;

			n++;
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
		}
	}
}

void displaySphere(float radius) {

	int b;
	glScalef(0.0125 * radius, 0.0125 * radius, 0.0125 * radius);
	//glRotatef (90, 1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (b = 0; b < VertexCount; b++)
	{
		glTexCoord2f(VERTEX[b].U, VERTEX[b].V);
		glVertex3f(VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
	}

	for (b = 0; b < VertexCount; b++)
	{
		glTexCoord2f(VERTEX[b].U, -VERTEX[b].V);
		glVertex3f(VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
	}

	glEnd();
}

void eglSphere(float radius, unsigned int texture_id)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_id);
	CreateSphere(radius, 0, 0, 0);
	displaySphere(5);
	glPopMatrix();
}