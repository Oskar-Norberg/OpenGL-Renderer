#ifndef GLSLBUFFEROBJECTS_H
#define GLSLBUFFEROBJECTS_H

#define VIEWPROJECTIONBINDINGPOINT 0

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct ViewProjectionMatrices {
	glm::mat4 view;
	glm::mat4 projection;
} ViewProjectionMatrices;

#endif
