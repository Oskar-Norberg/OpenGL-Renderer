#include "../include/lightManager.h"

DirectionalLight* LightManager::setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	lights.directionalLight = { direction, ambient, diffuse, specular };
	return &(lights.directionalLight);
}

PointLight* LightManager::addPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
	PointLight* pointLight = &lights.pointLights[lights.nrOfPointLights];
	(*pointLight) = { position, constant, ambient, linear, diffuse, quadratic, specular };
	lights.nrOfPointLights++;
	return pointLight;
}

Spotlight* LightManager::addSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
	float cutoff = glm::cos(glm::radians(cutoffAngle));
	float outerCutoff = glm::cos(glm::radians(outerCutoffAngle));
	Spotlight* spotlight = &lights.spotlights[lights.nrOfSpotlights];
	(*spotlight) = { position, cutoff, direction, outerCutoff, ambient, constant, diffuse, linear, specular, quadratic };
	lights.nrOfSpotlights++;
	return spotlight;
}

Lights LightManager::getLights() {
	return lights;
}