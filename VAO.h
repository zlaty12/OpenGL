#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint NumComponent, GLenum type, GLsizeiptr stride, void* offset);
	// Binds  VAO
	void Bind();
	// Unbinds  VAO
	void Unbind();
	// Deletes  VAO
	void Delete();
};
#endif