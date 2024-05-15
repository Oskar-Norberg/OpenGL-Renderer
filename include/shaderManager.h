#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "shader.h"
#include "lights.h"
#include "camera.h"

#include <string>
#include <vector>

class ShaderManager {
public:
	ShaderManager();

	~ShaderManager();

	Shader* createShader(std::string vertexPath, std::string fragmentPath);

	void setCameraMatrices(Camera* camera);

	void setLights(Lights lights);

private:
	unsigned int viewProjectionUBO, lightsUBO;
	std::vector<Shader*> shaders;
};

#endif