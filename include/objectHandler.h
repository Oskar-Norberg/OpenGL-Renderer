#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include "shader.h"
#include "model.h"
#include "object.h"

#include <vector>


class ObjectHandler {
public:
	~ObjectHandler();

	Object* createOpaqueObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader);

	Object* createTransparentObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader);

	void draw(glm::vec3 cameraPosition);

private:
	std::vector<Object*> opaqueObjects;
	std::vector<Object*> transparentObjects;
};

#endif