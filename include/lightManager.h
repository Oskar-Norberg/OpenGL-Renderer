#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "lights.h" 

class LightManager {
public:
	DirectionalLight* setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		lights.directionalLight = { direction, constant, ambient, linear, diffuse, quadratic, specular };
		return &(lights.directionalLight);
	}

	PointLight* addPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		PointLight* pointLight = &lights.pointLights[lights.nrOfPointLights];
		(*pointLight) = { position, constant, ambient, linear, diffuse, quadratic, specular };
		lights.nrOfPointLights++;
		return pointLight;
	}

	Spotlight* addSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		float cutoff = glm::cos(glm::radians(cutoffAngle));
		float outerCutoff = glm::cos(glm::radians(outerCutoffAngle));
		Spotlight* spotlight = &lights.spotlights[lights.nrOfSpotlights];
		(*spotlight) = { position, cutoff, direction, outerCutoff, ambient, constant, diffuse, linear, specular, quadratic };
		lights.nrOfSpotlights++;
		return spotlight;
	}

	Lights getLights() {
		return lights;
	}

private:
	Lights lights;
};

#endif