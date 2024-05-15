#include "../include/objectHandler.h"

#include <string>
#include <map>

ObjectHandler::~ObjectHandler() {
	for (Object* obj : opaqueObjects) {
		delete obj;
	}
	opaqueObjects.clear();
	for (auto object : transparentObjects) {
		delete object;
	}
	transparentObjects.clear();
}

Object* ObjectHandler::createOpaqueObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
	Object* object = new Object(position, scale, rotationAxis, rotationDegrees, model, shader);
	opaqueObjects.push_back(object);
	return object;
}

Object* ObjectHandler::createTransparentObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
	Object* object = new Object(position, scale, rotationAxis, rotationDegrees, model, shader);
	transparentObjects.push_back(object);
	return object;
}

void ObjectHandler::draw(glm::vec3 cameraPosition) {
	// Draw opaque objects
	for (size_t i = 0; i < opaqueObjects.size(); i++)
	{
		(*opaqueObjects[i]).draw();
	}

	// Draw transparent objects
	std::map<float, Object*> sorted;
	for (unsigned int i = 0; i < transparentObjects.size(); i++)
	{
		float distance = glm::length(cameraPosition - (*transparentObjects[i]).getPosition());
		sorted[distance] = transparentObjects[i];
	}

	for (std::map<float, Object*>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		it->second->draw();
	}
}
