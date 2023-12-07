#include "data.h"
#include "../lib/evalg.hpp"
#include <GL/gl.h>

#ifndef EVA_KSUCS_CG_ROBOT
#define EVA_KSUCS_CG_ROBOT

void renderRobotSolid(struct rotation_s* rotation, struct displaySettings_s* displaySettings, GLuint *textures);
void renderRobotWire(struct rotation_s* rotation, struct displaySettings_s* displaySettings);
void displayAxes();
void drawCamera(vec3<float> pos, vec3<float> facing);
void drawTree(GLuint leaf, GLuint bark);

#endif
