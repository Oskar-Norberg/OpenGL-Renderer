#include "../include/scene.h"

#include <glad/glad.h>

Scene::Scene(glm::vec4 backgroundColor) {
	this->backgroundColor = backgroundColor;
}

Object* Scene::createObject(bool transparent, std::string modelPath, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Shader* shader) {
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

Shader* Scene::createShader(std::string vertexPath, std::string fragmentPath) {
	return shaderManager.createShader(vertexPath, fragmentPath);
}

void Scene::createPostProcessingEffect(Shader* shader) {
	postProcessingManager = new PostProcessingManager(shader);
}

void Scene::draw(Camera* camera) {
	glBindFramebuffer(GL_FRAMEBUFFER, postProcessingManager->getFrameBuffer());
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shaderManager.setCameraMatrices(camera);
	objectHandler.draw((*camera).getPosition());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	postProcessingManager->drawQuad();
}

PointLight* Scene::createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
	PointLight* pointLight = lightManager.addPointLight(position, ambient, diffuse, specular, constant, linear, quadratic);
	setLights();
	return pointLight;
}

Spotlight* Scene::createSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
	Spotlight* spotlight = lightManager.addSpotlight(position, direction, cutoffAngle, outerCutoffAngle, ambient, diffuse, specular, constant, linear, quadratic);
	setLights();
	return spotlight;
}

DirectionalLight* Scene::setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	DirectionalLight* directionalLight = lightManager.setSun(direction, ambient, diffuse, specular);
	setLights();
	return directionalLight;
}

void Scene::setLights() {
	shaderManager.setLights(lightManager.getLights());
}