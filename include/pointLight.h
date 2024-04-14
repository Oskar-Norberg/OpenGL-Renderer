#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

class PointLight : public Light, public Object{
public:
	PointLight(glm::vec3 position, Model* model, Shader* shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
		: Light(ambient, diffuse, specular, constant, linear, quadratic),
		Object(position, model, shader) {

	}

};

#endif
