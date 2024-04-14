#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight() {

	}

	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
		: Light(ambient, diffuse, specular, constant, linear, quadratic)
	{
		this->direction = direction;
	}

	glm::vec3 getDirection() {
		return this->direction;
	}
private:
	glm::vec3 direction;
};

#endif
