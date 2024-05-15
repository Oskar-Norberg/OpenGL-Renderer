#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "shader.h"
#include "lights.h"
#include "GLSLBufferObjects.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <vector>
#include <string>

#include "shader.h"
#include "camera.h"

using std::vector;
using std::string;

class ShaderManager {
public:
	ShaderManager() {
		glGenBuffers(1, &viewProjectionUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, viewProjectionUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewProjectionMatrices), NULL, GL_STATIC_DRAW);

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Lights), NULL, GL_STATIC_DRAW);
	}

	~ShaderManager() {
		for (auto shader : shaders) {
			delete shader;
		}
		shaders.clear();

		glDeleteBuffers(1, &viewProjectionUBO);
		glDeleteBuffers(1, &lightsUBO);
	}

	Shader* createShader(string vertexPath, string fragmentPath) {
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

	void setCameraMatrices(Camera* camera) {
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

	void setLights(Lights lights) {
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

private:
	unsigned int viewProjectionUBO, lightsUBO;
	vector<Shader*> shaders;
};

#endif