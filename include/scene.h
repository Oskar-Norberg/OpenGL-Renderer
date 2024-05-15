#ifndef SCENE_H
#define SCENE_H

#include "shader.h"

#include "shaderManager.h"
#include "modelLoader.h"
#include "objectHandler.h"
#include "lightManager.h"

#include "lights.h"

class Scene {
public:
	Scene(glm::vec4 backgroundColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));

	Object* createObject(bool transparent, std::string modelPath, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Shader* shader);

	Shader* createShader(std::string vertexPath, std::string fragmentPath);

	void draw(Camera* camera);

	PointLight* createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	Spotlight* createSpotlight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float outerCutoffAngle, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	DirectionalLight* setSun(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

	void setLights();

private:
	ShaderManager shaderManager;
	ModelLoader modelLoader;
	ObjectHandler objectHandler;
	LightManager lightManager;

	glm::vec4 backgroundColor;
};

#endif