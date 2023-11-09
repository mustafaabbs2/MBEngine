#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
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

	// Define vertices for a green triangle
	GLfloat positions[] = {
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

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Clear color buffer bit
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the triangle
		glBegin(GL_TRIANGLES);
		glVertex3fv(&positions[0]);
		glVertex3fv(&positions[3]);
		glVertex3fv(&positions[6]);
		glEnd();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Destroy window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
