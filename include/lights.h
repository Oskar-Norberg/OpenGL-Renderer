#ifndef LIGHTS_H
#define LIGHTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct DirectionalLight {
	glm::vec3 direction;
	glm::vec3 ambient, diffuse, specular;
	float constant, linear, quadratic;
} DirectionalLight;

typedef struct PointLight {
	glm::vec3 position;
	glm::vec3 ambient, diffuse, specular;
	float constant, linear, quadratic;
} PointLight;

typedef struct Spotlight {
	glm::vec3 position, direction;
	float cutoff, outerCutoff;
	glm::vec3 ambient, diffuse, specular;
	float constant, linear, quadratic;
} Spotlight;

#endif