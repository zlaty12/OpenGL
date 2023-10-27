#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Construct the EBO and linking it to the indeces
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif