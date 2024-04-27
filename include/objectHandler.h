#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "shader.h"
#include "model.h"
#include "object.h"

class ObjectHandler {
public:
	~ObjectHandler() {
		for (Object* obj : opaqueObjects) {
			delete obj;
		}
		opaqueObjects.clear();
		for (auto object : transparentObjects) {
			delete object;
		}
		transparentObjects.clear();
	}

	Object* createOpaqueObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
		Object* object = new Object(position, scale, rotationAxis, rotationDegrees, model, shader);
		opaqueObjects.push_back(object);
		return object;
	}

	Object* createTransparentObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
		Object* object = new Object(position, scale, rotationAxis, rotationDegrees, model, shader);
		transparentObjects.push_back(object);
		return object;
	}

	void draw() {
		for (size_t i = 0; i < opaqueObjects.size(); i++)
		{
			(*opaqueObjects[i]).draw();
		}
	}

private:
	vector<Object*> opaqueObjects;
	vector<Object*> transparentObjects;
};

#endif