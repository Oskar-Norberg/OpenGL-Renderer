#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include "shader.h"
#include "object.h"
#include "model.h"

#include "pointLight.h"
#include "spotlight.h"
#include "directionalLight.h"

class Scene {
public:
	Scene(){
	}
private:
	vector<Object*> opaqueObjects;
	vector<Object*> transparentObjects;

	DirectionalLight sun;
	vector<PointLight*> pointLights;
	vector<Spotlight*> spotlights;

	glm::vec4 backgroundColor;
};

#endif