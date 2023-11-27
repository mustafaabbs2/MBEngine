 
#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>

std::string readShaderFile(const char* filePath);
GLuint compileShader(const char* shaderSource, GLenum shaderType);
std::vector<float> rearrangeCoordinates(const std::vector<float>& originalCoordinates);
void writeObjFile(const std::vector<float>& nodeCoordinates, const std::vector<int>& offsets, const std::string& filePath, bool tris);


const char* vertexSource = R"glsl(
#version 460 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)glsl";

const char* fragmentSource = R"glsl(
#version 460 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}

)glsl";


