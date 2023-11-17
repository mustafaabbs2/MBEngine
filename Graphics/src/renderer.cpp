
#define GLEW_STATIC
#define QT 0
#define IMGUI 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#if QT
#	include "QT\QtGUI.hpp"
#endif

#if IMGUI
#	include "imgui\imgui.h"
#	include "imgui\imgui_impl_glfw.h"
#	include "imgui\imgui_impl_opengl3.h"
#endif

static void setupImGUI(GLFWwindow* window)
{

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	const char* glsl_version = "#version 330";

	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

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

int main(int argc, char* argv[])
{
	// Initialize GLFW
	if(!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if(!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Set swap interval to 1 to enable vsync
	glfwSwapInterval(1);
	// Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Clear color buffer bit
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	setupImGUI(window);

	// Read and compile vertex shader
	std::string vertexShaderSource = readShaderFile("shaders/vertexShader.glsl");
	GLuint vertexShader = compileShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);

	// Read and compile fragment shader
	std::string fragmentShaderSource = readShaderFile("shaders/fragmentShader.glsl");
	GLuint fragmentShader = compileShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

	// Link shaders into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for program linking errors
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
		return -1;
	}

	GLfloat vertices[] = {
		0.5f,
		0.5f,
		0.0f, // top right
		-0.5f,
		0.5f,
		0.0f, // bottom left
		0.0f,
		-0.5f,
		0.0f // bottom center
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Create and bind a vertex array object (VAO)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Specify the layout of the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window))
	{
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Use the shader program...

		// Bind the VAO and draw the triangle
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Unbind the VAO
		glBindVertexArray(0);

		// render your GUI
		ImGui::Begin("Demo window");
		ImGui::Button("Hello!");
		ImGui::End();

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Destroy window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}