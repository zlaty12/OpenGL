#include"camera.h"


Camera::Camera(int width, int hight, glm::vec3 position)
{
	Camera::width = width;
	Camera::hight = hight;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float NearPlane, float FarPlaine, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, UP);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / hight), NearPlane, FarPlaine);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation,UP));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, UP));
	}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * UP;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -UP;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.1f;
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (ClickCamera)
		{
			glfwSetCursorPos(window, (width / 2), (hight / 2));
			ClickCamera = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (hight / 2)) / hight;
		float rotY = sensitivity * (float)(mouseX - (hight / 2)) / hight;

		glm::vec3 NewOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, UP)));
		

		if (!(glm::angle(NewOrientation, UP) <= glm::radians(5.0f)) || glm::angle(NewOrientation, -UP) <= glm::radians(5.0f))
		{
			Orientation = NewOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), UP);

		glfwSetCursorPos(window, (width / 2), (hight / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		ClickCamera = true;
	}

}