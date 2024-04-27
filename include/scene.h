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
	Scene(glm::vec4 backgroundColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f)) {
		this->backgroundColor = backgroundColor;
	}

	~Scene() {
		delete sun;
		for (auto pointLight : pointLights) {
			delete pointLight;
		}
		pointLights.clear();
		for (auto spotlight : spotlights) {
			delete spotlight;
		}
		spotlights.clear();
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
		PointLight* p = new PointLight(position, ambient, diffuse, specular, constant, linear, quadratic);
		pointLights.push_back(p);
		setLights();
		return p;
	}

	Spotlight* createSpotlight(glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		Spotlight* s = new Spotlight(position, direction, cutoff, outerCutoff, ambient, diffuse, specular, constant, linear, quadratic);
		spotlights.push_back(s);
		setLights();
		return s;
	}

	DirectionalLight* setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
		DirectionalLight* sun = new DirectionalLight(direction, ambient, diffuse, specular, constant, linear, quadratic);
		this->sun = sun;
		return sun;
	}

	void setLights() {
		shaderManager.setLights((*sun), pointLights, spotlights);
	}

private:
	ShaderManager shaderManager;
	ModelLoader modelLoader;
	ObjectHandler objectHandler;

	DirectionalLight* sun;
	vector<PointLight*> pointLights;
	vector<Spotlight*> spotlights;

	glm::vec4 backgroundColor;


};

#endif