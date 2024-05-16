#ifndef LIGHTS_H
#define LIGHTS_H

#define MAX_POINT_LIGHTS 10
#define MAX_SPOTLIGHTS 10

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

typedef struct DirectionalLight {
	alignas(sizeof(glm::vec4)) glm::vec3 direction;
	alignas(sizeof(glm::vec4)) glm::vec3 ambient;
	alignas(sizeof(glm::vec4)) glm::vec3 diffuse;
	alignas(sizeof(glm::vec4)) glm::vec3 specular;
} DirectionalLight;

typedef struct PointLight {
	glm::vec3 position;
	float constant;
	glm::vec3 ambient;
	float linear;
	glm::vec3 diffuse;
	float quadratic;
	alignas(sizeof(glm::vec4)) glm::vec3 specular;
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