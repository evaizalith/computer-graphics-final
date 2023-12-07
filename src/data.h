// Eva Powlison

// This file stores global variables
// Storing all of my global data in structs allows for cleaner data sharing between files

#include <stdbool.h>
#include "GL/gl.h"

#ifndef EVA_KSUCS_CG_DATA
#define EVA_KSUCS_CG_DATA

struct mouse_s {
	GLint leftMouse;
	GLint rightMouse;
	int x;
	int y; 
    bool capture;
    float sensitivity;
};



struct camera_s {
	float x, y, z;
	float fx, fy, fz; 
	float theta, phi, radius; 
};

struct displaySettings_s {
	bool DISPLAY_SOLID;
	bool DISPLAY_WIRE;
	bool DISPLAY_MODEL;
	bool DISPLAY_AXIS; 
	bool DISPLAY_COLOR;
	bool DISPLAY_ANYTHING; 
	bool CULLING; 
	bool GUNDAM; 
	bool PLAY_ANIMATION;
	bool SHOW_PATH;
	bool LINE_MODE;
	float R;
	float G;
	float B;
};

struct rotation_s {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat l_elbow;
	GLfloat l_shoulder;
	GLfloat l_hip;
	GLfloat l_knee;
	GLfloat r_elbow;
	GLfloat r_shoulder;
	GLfloat r_hip;
	GLfloat r_knee;
};

typedef struct mouseKeyboard_s mouseKeyboard_t; 
typedef struct displaySettings_s displaySettings_t; 
typedef struct rotation_s rotation_t; 
typedef struct camera_s camera_t;

#endif 