#include "../include/shaderManager.h"

#include "glad/glad.h"

#include "../include/GLSLBufferObjects.h"

ShaderManager::ShaderManager() {
	glGenBuffers(1, &viewProjectionUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, viewProjectionUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewProjectionMatrices), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &lightsUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Lights), NULL, GL_STATIC_DRAW);
}

ShaderManager::~ShaderManager() {
	for (auto shader : shaders) {
		delete shader;
	}
	shaders.clear();

	glDeleteBuffers(1, &viewProjectionUBO);
	glDeleteBuffers(1, &lightsUBO);
}

Shader* ShaderManager::createShader(std::string vertexPath, std::string fragmentPath) {
	// Prevent loading same shader multiple times
	for (size_t i = 0; i < shaders.size(); i++)
	{
		if (strcmp((*shaders[i]).getVertexPath().c_str(), vertexPath.c_str()) == 0) {
			if (strcmp((*shaders[i]).getFragmentPath().c_str(), fragmentPath.c_str()) == 0) {
				printf("same shader found\n");
				return shaders[i];
			}
		}
	}

	Shader* tmp = new Shader(vertexPath, fragmentPath);
	shaders.push_back(tmp);
	return tmp;
}

void ShaderManager::setCameraMatrices(Camera* camera) {
	// Bind to uniform buffer object
	glBindBuffer(GL_UNIFORM_BUFFER, viewProjectionUBO);


	for (size_t i = 0; i < shaders.size(); i++)
	{
		// Set index to view projection matrices for each shader
		unsigned int viewProjectionIndex = glGetUniformBlockIndex((*shaders[i]).ID, "ViewProjectionMatrices");
		glUniformBlockBinding((*shaders[i]).ID, viewProjectionIndex, VIEW_PROJECTION_BINDINGPOINT);
	}
	// Bind to said index
	glBindBufferBase(GL_UNIFORM_BUFFER, VIEW_PROJECTION_BINDINGPOINT, viewProjectionUBO);

	ViewProjectionMatrices tmp = { (*camera).getViewMatrix(), (*camera).getProjectionMatrix(), (*camera).getPosition() };

	// Send data
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ViewProjectionMatrices), &tmp);
}

void ShaderManager::setLights(Lights lights) {
	// Bind to uniform buffer object
	glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);


	for (size_t i = 0; i < shaders.size(); i++)
	{
		// Set index to lights for each shader
		unsigned int lightsIndex = glGetUniformBlockIndex((*shaders[i]).ID, "Lights");
		glUniformBlockBinding((*shaders[i]).ID, lightsIndex, LIGHTS_BINDINGPOINT);
	}

	// Bind to said index
	glBindBufferBase(GL_UNIFORM_BUFFER, LIGHTS_BINDINGPOINT, lightsUBO);

	// Directional Light Data
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Lights), &lights);
}
