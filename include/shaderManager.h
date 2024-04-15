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

#include "directionalLight.h"
#include "pointLight.h"
#include "spotlight.h"

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

	void setLights(DirectionalLight& directionalLight, vector<PointLight*> pointLights, vector<Spotlight*> spotlights) {
		for (size_t i = 0; i < shaders.size(); i++)
		{
			Shader shader = (*shaders[i]);
			shader.use();

			shader.setInt("nrOfPointLights", pointLights.size());
			shader.setInt("nrOfSpotlights", spotlights.size());

			// Directional light
			{
				string lightShaderLocation = "directionalLight.";
				shader.setVec3(lightShaderLocation + "direction", directionalLight.getDirection());

				shader.setVec3(lightShaderLocation + "ambient", directionalLight.getAmbient());
				shader.setVec3(lightShaderLocation + "diffuse", directionalLight.getDiffuse());
				shader.setVec3(lightShaderLocation + "specular", directionalLight.getSpecular());

				shader.setFloat(lightShaderLocation + "constant", directionalLight.getConstant());
				shader.setFloat(lightShaderLocation + "linear", directionalLight.getLinear());
				shader.setFloat(lightShaderLocation + "quadratic", directionalLight.getQuadratic());
			}

			//Point lights
			for (size_t i = 0; i < pointLights.size(); i++)
			{
				PointLight tmpPointLight = (*pointLights[i]);
				string lightShaderLocation = "pointLights[" + std::to_string(i) + "].";

				shader.setVec3(lightShaderLocation + "position", tmpPointLight.getPosition());

				shader.setVec3(lightShaderLocation + "ambient", tmpPointLight.getAmbient());
				shader.setVec3(lightShaderLocation + "diffuse", tmpPointLight.getDiffuse());
				shader.setVec3(lightShaderLocation + "specular", tmpPointLight.getSpecular());

				shader.setFloat(lightShaderLocation + "constant", tmpPointLight.getConstant());
				shader.setFloat(lightShaderLocation + "linear", tmpPointLight.getLinear());
				shader.setFloat(lightShaderLocation + "quadratic", tmpPointLight.getQuadratic());
			}

			//Spotlight
			for (size_t i = 0; i < spotlights.size(); i++)
			{
				Spotlight tmpSpotLight = (*spotlights[i]);
				string lightShaderLocation = "spotlights[" + std::to_string(i) + "].";

				shader.setVec3(lightShaderLocation + "position", tmpSpotLight.getPosition());
				shader.setVec3(lightShaderLocation + "direction", tmpSpotLight.getDirection());

				shader.setFloat(lightShaderLocation + "cutoff", tmpSpotLight.getCutoff());
				shader.setFloat(lightShaderLocation + "outerCutoff", tmpSpotLight.getOutercutoff());

				shader.setVec3(lightShaderLocation + "ambient", tmpSpotLight.getAmbient());
				shader.setVec3(lightShaderLocation + "diffuse", tmpSpotLight.getDiffuse());
				shader.setVec3(lightShaderLocation + "specular", tmpSpotLight.getSpecular());

				shader.setFloat(lightShaderLocation + "constant", tmpSpotLight.getConstant());
				shader.setFloat(lightShaderLocation + "linear", tmpSpotLight.getLinear());
				shader.setFloat(lightShaderLocation + "quadratic", tmpSpotLight.getQuadratic());
			}
		}

	}

	void setWindShaderUniforms(Shader* shader) {
		(*shader).use();
		(*shader).setFloat("time", float(glfwGetTime()));
		(*shader).setFloat("windSpeed", 1.0f);
		(*shader).setFloat("windStrength", 0.5f);
	}

private:
	vector<Shader*> shaders;
};

#endif