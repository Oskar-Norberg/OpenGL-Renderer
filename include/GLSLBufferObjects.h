#ifndef GLSLBUFFEROBJECTS_H
#define GLSLBUFFEROBJECTS_H

#define VIEW_PROJECTION_BINDINGPOINT 0
#define LIGHTS_BINDINGPOINT 1

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lights.h"

typedef struct ViewProjectionPositionMatrices {
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 viewPosition;
} ViewProjectionMatrices;

#endif
