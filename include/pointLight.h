#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

class PointLight : public Light{
public:
	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
		: Light(ambient, diffuse, specular, constant, linear, quadratic) {
		this->position = position;
	}
	glm::vec3 getPosition() {
		return this->getPosition;
	}
private:
	glm::vec3 position;
};

#endif
