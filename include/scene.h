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

#include "lights.h"

class Scene {
public:
	Scene(glm::vec4 backgroundColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f)) {
		this->backgroundColor = backgroundColor;
	}

	Object* createObject(bool transparent, std::string modelPath, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Shader* shader) {
		Model* m = modelLoader.loadModel(modelPath);
		Object* o;
		if (transparent) {
			o = objectHandler.createTransparentObject(position, scale, rotationAxis, rotationDegrees, m, shader);
		}
		else {
			o = objectHandler.createOpaqueObject(position, scale, rotationAxis, rotationDegrees, m, shader);
		}
		return o;
	}

	Shader* createShader(std::string vertexPath, std::string fragmentPath) {
		return shaderManager.createShader(vertexPath, fragmentPath);
	}

	void draw(Camera* camera) {
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderManager.setCameraMatrices(camera);
		objectHandler.draw((*camera).getPosition());
	}

	PointLight* createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		PointLight* pointLight = &lights.pointLights[lights.nrOfPointLights];
		(*pointLight) = { position, constant, ambient, linear, diffuse, quadratic, specular };
		lights.nrOfPointLights++;
		setLights();
		return pointLight;
	}

	Spotlight* createSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		float cutoff = glm::cos(glm::radians(cutoffAngle));
		float outerCutoff = glm::cos(glm::radians(outerCutoffAngle));
		Spotlight* spotlight = &lights.spotlights[lights.nrOfSpotlights];
		(*spotlight) = { position, cutoff, direction, outerCutoff, ambient, constant, diffuse, linear, specular, quadratic };
		lights.nrOfSpotlights++;
		setLights();
		return spotlight;
	}

	DirectionalLight* setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		lights.directionalLight = { direction, constant, ambient, linear, diffuse, quadratic, specular };
		return &(lights.directionalLight);
	}

	void setLights() {
		shaderManager.setLights(lights);
	}

private:
	ShaderManager shaderManager;
	ModelLoader modelLoader;
	ObjectHandler objectHandler;

	Lights lights;

	glm::vec4 backgroundColor;
};

#endif