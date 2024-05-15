#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "lights.h" 

class LightManager {
public:
	DirectionalLight* setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	PointLight* addPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	Spotlight* addSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

	Lights getLights();

private:
	Lights lights;
};

#endif