
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


enum class Shape {
  TRIANGLE,
  RECTANGLE,
  FACET,
};

void Render(GLFWwindow* window, Shape shape);
void RenderWithGUI();