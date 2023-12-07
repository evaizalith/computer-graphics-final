// Eva Powlison

// This code contains functions for loading textures in OpenGL 

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "load_texture.h"

GLuint eglLoadBMP(const char *filePath) {
    unsigned char header[54];
    unsigned int dataStart; 
    unsigned int width;
    unsigned int height;
    unsigned int imageSize;

    FILE *image = fopen(filePath, "rb");
    if (!image) {
        printf("[EGL] ERROR: Failed to open image %s\n", filePath);
        return 0; 
    }

    // BMP files must have a header that is 54 bytes long
    if (fread(header, 1, 54, image) != 54) {
        printf("[EGL] ERROR: %s is not a correct BMP file!", filePath);
        return 0;
    }

    // BMP file headers must begin with B and M 
    if (header[0] != 'B' || header[1] != 'M') {
        printf("EGL] ERROR: %s is not a correct BMP file!", filePath);
        return 0;
    }

    dataStart = *(int*)&(header[0x0A]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    imageSize = *(int*)&(header[0x22]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataStart == 0) dataStart = 54;

    unsigned char *data[imageSize];

    fread(data, 1, imageSize, image);
    fclose(image);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    //printf("%s loaded as a %ix%i texture id %i\n", filePath, width, height, textureID);

    return textureID;
}