#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main()
{
	// initializing GLFW
	glfwInit();

	
	//Tell GLFW the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Telling GLFW that core profile was used. the core profile contains the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Adding verticis cordinets between -1 nad 1.
	GLfloat vertices[] =
	{
		-0.5, -0.5 * float(sqrt(3)) / 3,0.0f, // Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.f, // Lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper right
		-0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down


	};

	// adding indeces
	GLuint indeces[] =
	{
		0,3,5, // lower left triangle
		3,2,4, // lower riht triangle 
		5,4,1 // upper triangle
	};





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

	// Create Vertex Shader Object and ger reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into maching code
	glCompileShader(vertexShader);

	// Create Fragment Object and its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	// Compile the Vertex Shader into maching code
	glCompileShader(fragmentShader);

	// Create Shader Program object and get reference
	GLuint shaderProgram = glCreateProgram();
	// Attach Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap up shader together into a shader program
	glLinkProgram(shaderProgram);

	// Delete Vertex and fragment shader 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference to Vertex Array Object and Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate VAO and VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind Vortex Array Object
	glBindVertexArray(VAO);

	// Bind The VBO shader specifing its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Add the verteces to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Binding EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Add the indeces to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	// Configer Vertex Attributs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex ATTributes
	glEnableVertexAttribArray(0);

	// Bind VBO and VAO to 0 so it doesnt modify the exising VBO na VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// change window background color
	glClearColor(0.06f,0.13f,0.17f, 1.0f);
	//clearing the backbuffer and assigning the new color
	glClear(GL_COLOR_BUFFER_BIT);
	// swaping front and back buffers
	glfwSwapBuffers(window);
	
	// contenius runing main while the loop is active
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.06f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell openGL what shader program to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL know to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_Triangles primitive 
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Takes care of GLFW evnets
		glfwPollEvents();
	}

	// Delete all the objects 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	// Destroies the windw before it ends the program
	glfwDestroyWindow(window);
	// Terminates GLFW before ending the program.
	glfwTerminate();
	return 0;
	
}