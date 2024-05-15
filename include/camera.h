#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float yaw, float pitch, glm::vec3 position, glm::vec3 direction, glm::vec3 upwards, glm::mat4 projection);
	void handleMouseMovement(float xOffset, float yOffset);
	void handleKeyboard(glm::vec3 direction, float deltaTime);

	void setSprint(bool sprint);
	void setCrouch(bool crouch);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPosition();
	glm::vec3 getDirection();
private:
	float yaw, pitch;
	bool sprint, crouch;
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 upwards;
	glm::vec3 worldUp;
};
#endif
