#ifndef EVA_CAMERA
#define EVA_CAMERA

#include <string>
#include "../lib/evalg.hpp"

// I think implementing this camera counts as a traumatic experience.
class camera {
public:
    camera();
    camera(camera&);

    void updateCamera(); // Main camera function to call
    void keyboardMovement(std::string);
    void mouseMovement(float dx, float dy); // Free camera movement, FPS like
    void mouseArcball(float dx, float dy); // Arcball camera movement

    void setPos(vec3<float> n_pos);
    void setForward(vec3<float> n_forward);
    void setUp(vec3<float> n_up);
    void setAngle(float t, float p);

    vec3<float> getPos()     { return pos; };
    vec3<float> getForward() { return forward; };
    vec3<float> getUp()      { return up; };
    vec3<float> getRight()   { return right; };
    mat3<float> getMatrix()  { return viewMatrix; };

    void debugPrint();


private:
    vec3<float> pos;    // Current coordinates
    vec3<float> forward; // Coordinates camera is looking at
    vec3<float> up;     // Up vector
    vec3<float> right;

    // The view matrix encodes coordinates from the camera's perspective.
    // x is the camera's view forward
    // y is up from the camera's perspective
    // z is to the right of the camera
    mat3<float> viewMatrix; 

    float theta;
    float phi;

    void setRight() { right = forward.cross(up); right.normalize(); };
    void updateMatrix();
};

#endif