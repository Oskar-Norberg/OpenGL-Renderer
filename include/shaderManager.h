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

using std::vector;
using std::string;

class ShaderManager {
public:
	ShaderManager() {
	}

	Shader* createShader(string vertexPath, string fragmentPath) {
		Shader* tmp = new Shader(vertexPath.c_str(), fragmentPath.c_str());
		shaders.push_back(tmp);
		return tmp;
	}

private:
	vector<Shader*> shaders;
};

#endif