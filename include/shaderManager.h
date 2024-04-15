#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "shader.h"

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
		for (size_t i = 0; i < shaders.size(); i++)
		{
			(*shaders[i]).use();
			(*shaders[i]).setMat4("projection", (*camera).getProjectionMatrix());
			(*shaders[i]).setMat4("view", (*camera).getViewMatrix());
			(*shaders[i]).setVec3("viewPos", (*camera).getPosition());
		}
	}

private:
	vector<Shader*> shaders;
};

#endif