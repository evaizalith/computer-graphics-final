#include "data.h"

#ifndef EVA_KSUCS_CG_PATHS
#define EVA_KSUCS_CG_PATHS

void circlePath(int time, struct rotation_s* rotation);
void linePath(int time);

void drawCirclePath();
void drawLinePath();

void drawCircle(GLfloat, GLfloat, GLfloat, GLfloat, GLint);

#endif 