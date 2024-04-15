#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"

#include <string>

class Object
{
public:
	Object(glm::vec3 position, Model* model, Shader* shader) {
		this->position = position;
		this->model = model;
		this->shader = shader;
	}

	void draw() {
		(*shader).use();
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, position);
		(*shader).setMat4("model", modelMat);
		(*model).draw((*shader));
	}

	glm::vec3 getPosition() {
		return this->position;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	string getPath() {
		return (*model).getModelPath();
	}

	Model* getModel() {
		return model;
	}

private:
	glm::vec3 position;
	Model* model;
	Shader* shader;
};
#endif