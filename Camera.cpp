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