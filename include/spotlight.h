#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"

class Spotlight : public Light {
public:
	Spotlight(glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
		: Light(ambient, diffuse, specular, constant, linear, quadratic) {
		this->position = position;
		this->direction = direction;
		this->cutoff = glm::cos(glm::radians(cutoff));
		this->outerCutoff = glm::cos(glm::radians(outerCutoff));
	}

	glm::vec3 getPosition() {
		return this->position;
	}

	glm::vec3 getDirection() {
		return this->direction;
	}

	float getCutoff() {
		return this->cutoff;
	}

	float getOutercutoff() {
		return this->outerCutoff;
	}

private:
	glm::vec3 position;
	glm::vec3 direction;
	float cutoff, outerCutoff;
};

#endif
