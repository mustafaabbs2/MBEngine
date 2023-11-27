
#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>

// Function to read the contents of a file into a string
std::string readShaderFile(const char* filePath)
{
	std::ifstream file(filePath);
	if(!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return "";
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return content;
}



// Function to compile a shader
GLuint compileShader(const char* shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	// Check for shader compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
		return 0;
	}

	return shader;
}


std::vector<float>  rearrangeCoordinates(const std::vector<float>& originalCoordinates)
{
	// Ensure the size is a multiple of 3
	if(originalCoordinates.size() % 3 != 0)
	{
		std::cerr << "Invalid number of coordinates\n";
		return {};
	}

	size_t numPoints = originalCoordinates.size() / 3;

	std::vector<float> rearrangedCoordinates;

	for(size_t i = 0; i < numPoints; ++i)
	{
		float x = originalCoordinates[i];
		float y = originalCoordinates[i + numPoints];
		float z = originalCoordinates[i + 2 * numPoints];

		rearrangedCoordinates.push_back(x);
		rearrangedCoordinates.push_back(y);
		rearrangedCoordinates.push_back(z);
	}

	return rearrangedCoordinates;
}


void writeObjFile(const std::vector<float>& nodeCoordinates, const std::vector<int>& offsets, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    for (size_t i = 0; i < nodeCoordinates.size(); i += 3) {
        outFile << "v " << nodeCoordinates[i] << " " << nodeCoordinates[i + 1] << " " << nodeCoordinates[i + 2] << std::endl;
    }

    for (size_t i = 0; i < offsets.size(); ++i) {
        outFile << "f ";
        for (int j = 0; j < 3; ++j) {
            int index = offsets[i] + j - 3;  
            outFile << index << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}
