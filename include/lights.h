#ifndef LIGHTS_H
#define LIGHTS_H

#define MAX_POINT_LIGHTS 10
#define MAX_SPOTLIGHTS 10

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef struct DirectionalLight {
	glm::vec4 direction;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

} DirectionalLight;

typedef struct PointLight {
	glm::vec3 position;
	float constant;
	glm::vec3 ambient;
	float linear;
	glm::vec3 diffuse;
	float quadratic;
	glm::vec3 specular;
	float Ka;
} PointLight;

typedef struct Spotlight {
	glm::vec3 position;
	float cutoff;
	glm::vec3 direction;
	float outerCutoff;
	glm::vec3 ambient;
	float constant;
	glm::vec3 diffuse;
	float linear;
	glm::vec3 specular;
	float quadratic;
} Spotlight;

typedef struct Lights {
	DirectionalLight directionalLight;
	PointLight pointLights[MAX_POINT_LIGHTS];
	Spotlight spotlights[MAX_SPOTLIGHTS];
	int nrOfSpotlights;
	int nrOfPointLights;
} Lights;

#endif