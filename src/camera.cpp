#include "camera.hpp"
#include <string>
#include <GL/freeglut_std.h>

camera::camera() {
    pos = vec3<float>(0, 0, 0);
    forward = vec3<float>(1, 0, 0);
    up = vec3<float>(0, 1, 0);
    right = vec3<float>(0, 0, 1);
    theta = 0;
    phi = 0;
    viewMatrix = mat3<float>(forward, up, right);
}

camera::camera(camera& rhs) {
    pos = rhs.pos;
    forward = rhs.forward;
    up = rhs.up;
    right = rhs.right;
    theta = rhs.theta;
    phi = rhs.phi;
    viewMatrix = rhs.viewMatrix;
}

void camera::keyboardMovement(std::string direction) {
    float velocity = 1; // make this a function of delta time later

    if (direction == "forward") {
        pos += forward * velocity;
    }

    if (direction == "back") {
        pos -= forward * velocity;
    }

    if (direction == "left") {
        pos -= right * velocity;
    }

    if (direction == "right") {
        pos += right * velocity;
    }

    if (direction == "up") {
        pos += up * velocity;
    }

    if (direction == "down") {
        pos -= up * velocity;
    }

    setRight();
    forward.normalize();
    updateMatrix();
}

void camera::mouseMovement(float dx, float dy) {
    dx = (dx * 3.14159) / 180;
    dy = (dy * 3.14159) / 180;

    theta += dx;
    phi += dy;

    if(phi > 3.14159) phi = 3.14159;
    if (phi < -3.14159) phi = -3.14159;

    forward.x = cos(theta) * cos(phi);
    forward.y = sin(phi);
    forward.z = sin(theta) * cos(phi);
    forward.normalize();

    setRight();
    updateMatrix();
}

void camera::setPos(vec3<float> n_pos) { 
    pos = n_pos; 
};

void camera::setForward(vec3<float> n_forward) { 
    forward = n_forward; 
    setRight(); 
    updateMatrix();
};

void camera::setUp(vec3<float> n_up) { 
    up = n_up; 
    setRight(); 
    updateMatrix();
};

void camera::setAngle(float t, float p) { 
    theta = t; 
    phi = p; 
};

void camera::updateMatrix() {
    viewMatrix.setCol(0, forward);
    viewMatrix.setCol(1, up);
    viewMatrix.setCol(2, right);
}

void camera::debugPrint() {
    printf("Camera pos: "); pos.debugPrint();
    printf(", Forward: "); forward.debugPrint();
    printf(", Up: "); up.debugPrint();
    printf(", theta = %f, phi = %f", theta, phi);
    printf("\n");
}
