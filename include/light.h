#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"

class Light {
public:
	Light() {

	}

	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;

		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}


	glm::vec3 getAmbient() {
		return this->ambient;
	}

	glm::vec3 getDiffuse() {
		return this->diffuse;
	}

	glm::vec3 getSpecular() {
		return this->specular;
	}


	float getConstant() {
		return this->constant;
	}
	float getLinear() {
		return this->linear;
	}
	float getQuadratic() {
		return this->quadratic;
	}

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#endif