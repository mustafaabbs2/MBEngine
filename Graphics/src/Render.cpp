#include "Render.hpp"
#include "ShaderUtils.hpp"
#include "ImguiUtils.hpp"
#include "WindowUtils.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

void RenderBox()
{

	std::vector<float> nodeCoordinates = {-1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1,
										  -1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1};

	std::vector<float> offsets = {3, 6, 9, 12, 15, 18, 21, 24};

	std::cout << nodeCoordinates.size();

	if(!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", nullptr, nullptr);
	if(!window)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		return;
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

	//do I need this? it's too small
	float scale_factor = 20;
	GLint scaleLocation = glGetUniformLocation(shaderProgram, "scale");
	glUniform1f(scaleLocation, scale_factor);

	glUseProgram(shaderProgram);

	// Main rendering loop
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for(size_t i = 0; i < offsets.size(); ++i)
		{
			glDrawArrays(GL_LINE_LOOP, offsets[i], offsets[i]);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
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