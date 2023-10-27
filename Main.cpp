#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices 
GLfloat vertices[] =
{
	//      Cordinets                            Color
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	0.8f, 0.3f, 0.02f,	 // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		1.0f, 0.3f, 0.25f,	 // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	0.6f, 0.7f, 0.3f,	// Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	 0.5f, 0.3f, 0.3f,	// Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	1.0f , 0.7f, 0.5f,	 // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.6f, 0.4f, 0.1f	 // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//  GLFW core profile 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(800, 800, "UniOpenGL", NULL, NULL);
	// Error check for window
	if (window == NULL)
	{
		std::cout << " Window faild" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD 
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO atributes to VAO
	VAO1.LinkAttrib(VBO1, 0,3, GL_FLOAT,6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3* sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// cler the back buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL what shader program to use
		shaderProgram.Activate();
		// Bind the VAO 
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}



	// Delete all created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window 
	glfwDestroyWindow(window);
	// Terminate GLFW 
	glfwTerminate();
	return 0;
}