#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include "shader.h"

#include "shaderManager.h"
#include "modelLoader.h"
#include "objectHandler.h"

#include "pointLight.h"
#include "spotlight.h"
#include "directionalLight.h"

class Scene {
public:
	Scene(){
	}

	PointLight* createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		PointLight* p = new PointLight(position, ambient, diffuse, specular, constant, linear, quadratic);
		pointLights.push_back(p);
		setLights();
		return p;
	}

	Spotlight* createSpotlight(glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		Spotlight* s = new Spotlight(position, direction, cutoff, outerCutoff, ambient, diffuse, specular, constant, linear, quadratic);
		spotlights.push_back(s);
		return s;
	}

	

private:
	ShaderManager shaderManager;
	ModelLoader modelLoader;
	ObjectHandler objectHandler;

	DirectionalLight sun;
	vector<PointLight*> pointLights;
	vector<Spotlight*> spotlights;

	glm::vec4 backgroundColor;

	void setLights() {
		shaderManager.setLights(sun, pointLights, spotlights);
	}
};

#endif