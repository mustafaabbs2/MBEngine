#define GLEW_STATIC
#include "ImguiUtils.hpp"
#include "Render.hpp"
#include "ShaderUtils.hpp"
#include "WindowUtils.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

void Render(GLFWwindow* window, Shape shape, bool withGui = false)
{

	std::vector<float> nodeCoordinates;
	std::vector<int> offsets;
	int skip;


	if(shape == Shape::TRIANGLE)
	{

		nodeCoordinates = {-1,
						   -1,
						   -0.5,
						   1,
						   -1,
						   -1,
						   1,
						   1,
						   -1, // First triangle
						   -1,
						   1,
						   -0.5,
						   1,
						   1,
						   -1,
						   1,
						   1,
						   -1}; // Second triangle

		offsets = {3, 6};
		writeObjFile(nodeCoordinates, offsets, "triangle.obj", true);
		skip = 3;
	}

	if(shape == Shape::RECTANGLE)
	{
		nodeCoordinates = {-1, -1, -0.5, 1, -1, -1, 1, 1, -1, -1, 1, -1,
						   -1, -1, 1,	1, -1, 1,  1, 1, 1,  -1, 1, 1};

		offsets = {3, 6, 9, 12, 15, 18, 21, 24};
		skip = 4;
	}

	if(shape == Shape::FACET)
	{
		std::vector<float> nodeCoordinatesUnconverted;
		nodeCoordinatesUnconverted = {
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005,
			0.0005, 0.0008, 0.001,  0.001,  0.0008, 0.0008, 0.001,  0.001,  0.0008, 0.0008, 0.001,
			0.001,  0.0008, 0.0008, 0.001,  0.001,  0.0008, 0.0008, 0.001,  0.001,  0.0008, 0.0006,
			0.0008, 0.0008, 0.0006, 0,		0.0002, 0.0002, 0,		0.0004, 0.0006, 0.0006, 0.0004,
			0.0002, 0.0004, 0.0004, 0.0002, 0.0002, 0.0004, 0.0004, 0.0002, 0.0006, 0.0008, 0.0008,
			0.0006, 0.0004, 0.0006, 0.0006, 0.0004, 0,		0.0002, 0.0002, 0,		0,		0.0002,
			0.0002, 0,		0,		0.0002, 0.0002, 0,		0,		0.0002, 0.0002, 0,		0.0002,
			0.0004, 0.0004, 0.0002, 0.0002, 0.0004, 0.0004, 0.0002, 0.0006, 0.0008, 0.0008, 0.0006,
			0.0004, 0.0006, 0.0006, 0.0004, 0.0004, 0.0006, 0.0006, 0.0004, 0.0002, 0.0004, 0.0004,
			0.0002, 0.0006, 0.0008, 0.0008, 0.0006, 0.0006, 0.0008, 0.0008, 0.0006, 0.0004, 0.0006,
			0.0006, 0.0004, 0.0004, 0.0004, 0.0006, 0.0006, 0.0006, 0.0006, 0.0008, 0.0008, 0.0008,
			0.0008, 0.001,  0.001,  0,		0,		0.0002, 0.0002, 0.0002, 0.0002, 0.0004, 0.0004,
			0,		0,		0.0002, 0.0002, 0,		0,		0.0002, 0.0002, 0,		0,		0.0002,
			0.0002, 0,		0,		0.0002, 0.0002, 0.0008, 0.0008, 0.001,  0.001,  0.0008, 0.0008,
			0.001,  0.001,  0.0008, 0.0008, 0.001,  0.001,  0.0008, 0.0008, 0.001,  0.001,  0.0004,
			0.0004, 0.0006, 0.0006, 0.0002, 0.0002, 0.0004, 0.0004, 0.0006, 0.0006, 0.0008, 0.0008,
			0.0006, 0.0006, 0.0008, 0.0008, 0.0002, 0.0002, 0.0004, 0.0004, 0.0002, 0.0002, 0.0004,
			0.0004, 0.0002, 0.0002, 0.0004, 0.0004, 0.0004, 0.0004, 0.0006, 0.0006, 0.0004, 0.0004,
			0.0006, 0.0006, 0.0004, 0.0004, 0.0006, 0.0006, 0.0006, 0.0006, 0.0008, 0.0008, 0.0006,
			0.0006, 0.0008, 0.0008};

		nodeCoordinates = rearrangeCoordinates(nodeCoordinatesUnconverted);

		std::transform(nodeCoordinates.begin(),
					   nodeCoordinates.end(),
					   nodeCoordinates.begin(),
					   [](float x) { return x * (float)1000.0; });


		offsets = {4,  8,  12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52,
				   56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100};

		writeObjFile(nodeCoordinates, offsets, "facet.obj", false);		
		skip = 4;

	}

	if(withGui)
		setupImGUI(window);

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//can give the GPU pointer here for buffer here:
	glBufferData(GL_ARRAY_BUFFER,
				 nodeCoordinates.size() * sizeof(float),
				 nodeCoordinates.data(),
				 GL_STATIC_DRAW);

	//glGenBuffer.. -> needs connectivity

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	// Create the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint scaleLocation = glGetUniformLocation(shaderProgram, "scale");
	glUseProgram(shaderProgram);


	// Main rendering loop
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if(withGui)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		for(size_t i = 0; i < offsets.size(); ++i)
		{
			glUniform1f(scaleLocation, 20.0f); // Set scale here if needed
			glDrawArrays(GL_LINE_LOOP, 0, nodeCoordinates.size() / 3);
			//gldrawelement array => needs connectivity
		}

		if(withGui)
		{
			ImGui::Begin("Demo window");
			ImGui::Button("Hello!");
			ImGui::End();

			// Render ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	if(withGui)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
