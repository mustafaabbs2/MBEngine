#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / height, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}