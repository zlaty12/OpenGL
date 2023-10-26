#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// initializing GLFW
	glfwInit();


	//Tell GLFW the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Telling GLFW that core profile was used. the core profile contains the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Creating a window for GLFW
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLForUni", NULL, NULL);
	//Checking if windwo is a null ponter and it fails to create
	if (window == NULL)
	{
		std::cout << "Window Error" << std::endl;
		glfwTerminate();
		return -1;
	}
	//adding the window to the curent context
	glfwMakeContextCurrent(window);

	//Adding glad
	gladLoadGL();

	// Specify the window size
	glViewport(0,0,800,800);
	// change window background color 
	glClearColor(0.06f,0.13f,0.17f, 1.0f);
	//clearing the backbuffer and assigning the new color
	glClear(GL_COLOR_BUFFER_BIT);
	// swaping front and back buffers
	glfwSwapBuffers(window);
	
	// contenius runing main while the loop is active
	while (!glfwWindowShouldClose(window))
	{
		// Takes care of GLFW evnets
		glfwPollEvents();
	}
	// Destroies the windw before it ends the program
	glfwDestroyWindow(window);
	// Terminates GLFW before ending the program
	glfwTerminate();
	return 0;
	//sss
}