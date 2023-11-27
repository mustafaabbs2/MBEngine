#define GLEW_STATIC
#include "ImguiUtils.hpp"
#include "Render.hpp"
#include "ShaderUtils.hpp"
#include "WindowUtils.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

void Render(GLFWwindow* window, Shape shape)
{

	std::vector<float> nodeCoordinates, offsets;

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
	}

	if(shape == Shape::RECTANGLE)
	{
		nodeCoordinates = {-1, -1, -0.5, 1, -1, -1, 1, 1, -1, -1, 1, -1,
						   -1, -1, 1,	1, -1, 1,  1, 1, 1,  -1, 1, 1};

		offsets = {3, 6, 9, 12, 15, 18, 21, 24};
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
					   [](float x) { return x * (float)500.0; });

		// for(size_t i = 0; i < 300; i++)
		// {
		// 	std::cout << nodeCoordinates[i] << " ";
		// }

		offsets = {4,  8,  12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52,
				   56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100};
	}

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,
				 nodeCoordinates.size() * sizeof(float),
				 nodeCoordinates.data(),
				 GL_STATIC_DRAW);

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

		for(size_t i = 0; i < offsets.size(); ++i)
		{
			glUniform1f(scaleLocation, 20.0f); // Set scale here if needed
			glDrawArrays(GL_LINE_LOOP, 0, nodeCoordinates.size() / 3);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

// void RenderWithGUI()
// {
// 	// Initialize GLFW
// 	if(!glfwInit())
// 	{
// 		std::cerr << "Failed to initialize GLFW" << std::endl;
// 		return;
// 	}

// 	// Create a windowed mode window and its OpenGL context
// 	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
// 	if(!window)
// 	{
// 		std::cerr << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return;
// 	}

// 	// Make the window's context current
// 	glfwMakeContextCurrent(window);

// 	// Set swap interval to 1 to enable vsync
// 	glfwSwapInterval(1);
// 	// Initialize GLEW
// 	glewExperimental = true; // Needed in core profile
// 	if(glewInit() != GLEW_OK)
// 	{
// 		std::cerr << "Failed to initialize GLEW" << std::endl;
// 		glfwDestroyWindow(window);
// 		glfwTerminate();
// 		return;
// 	}

// 	// Enable depth testing
// 	glEnable(GL_DEPTH_TEST);

// 	// Clear color buffer bit
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	setupImGUI(window);

// 	//When reading from .glsl

// 	// // Read and compile vertex shader
// 	// std::string vertexSource = readShaderFile("shaders/vertexShader.glsl");
// 	GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);

// 	// // Read and compile fragment shader
// 	// std::string fragmentSource = readShaderFile("shaders/fragmentShader.glsl");
// 	GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

// 	// Link shaders into a shader program
// 	GLuint shaderProgram = glCreateProgram();
// 	glAttachShader(shaderProgram, vertexShader);
// 	glAttachShader(shaderProgram, fragmentShader);
// 	glLinkProgram(shaderProgram);

// 	// Check for program linking errors
// 	GLint success;
// 	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
// 	if(!success)
// 	{
// 		char infoLog[512];
// 		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
// 		std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
// 		return;
// 	}

// 	GLfloat vertices[] = {
// 		0.5f,
// 		0.5f,
// 		0.0f, // top right
// 		-0.5f,
// 		0.5f,
// 		0.0f, // bottom left
// 		0.0f,
// 		-0.5f,
// 		0.0f // bottom center
// 	};

// 	GLuint vbo;
// 	glGenBuffers(1, &vbo);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 	// Create and bind a vertex array object (VAO)
// 	GLuint vao;
// 	glGenVertexArrays(1, &vao);
// 	glBindVertexArray(vao);

// 	// Specify the layout of the vertex data
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
// 	glEnableVertexAttribArray(0);

// 	//shaders have ben bound, you can delete them
// 	glDeleteShader(vertexShader);
// 	glDeleteShader(fragmentShader);

// 	// Loop until the user closes the window
// 	while(!glfwWindowShouldClose(window))
// 	{
// 		// feed inputs to dear imgui, start new frame
// 		ImGui_ImplOpenGL3_NewFrame();
// 		ImGui_ImplGlfw_NewFrame();
// 		ImGui::NewFrame();

// 		// Clear the color buffer
// 		glClear(GL_COLOR_BUFFER_BIT);

// 		// Use the shader program...
// 		glUseProgram(shaderProgram);

// 		// Bind the VAO and draw the triangle
// 		glBindVertexArray(vao);
// 		glDrawArrays(GL_TRIANGLES, 0, 3);

// 		// Unbind the VAO
// 		glBindVertexArray(0);
// 		//unbind the shader
// 		glUseProgram(0);

// 		// render your GUI
// 		ImGui::Begin("Demo window");
// 		ImGui::Button("Hello!");
// 		ImGui::End();

// 		// Render ImGui
// 		ImGui::Render();
// 		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

// 		// Swap front and back buffers
// 		glfwSwapBuffers(window);

// 		// Poll for and process events
// 		glfwPollEvents();
// 	}

// 	// Destroy window and terminate GLFW
// 	glfwDestroyWindow(window);
// 	glfwTerminate();

// 	ImGui_ImplOpenGL3_Shutdown();
// 	ImGui_ImplGlfw_Shutdown();
// 	ImGui::DestroyContext();

// }