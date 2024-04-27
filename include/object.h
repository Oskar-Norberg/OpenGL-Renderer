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
	Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
		this->position = position;
		
		this->scale = scale;

		this->rotationAxis = rotationAxis;
		this->rotationDegrees = rotationDegrees;

		this->model = model;
		this->shader = shader;
	}

	void draw() {
		(*shader).use();

		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, position);
		if (rotationDegrees)
		{
			modelMat = glm::rotate(modelMat, rotationDegrees, rotationAxis);
		}
		if (scale != glm::vec3(0.0f)) {
			modelMat = glm::scale(modelMat, scale);
		}

		(*shader).setMat4("model", modelMat);
		(*model).draw((*shader));
	}

	glm::vec3 getPosition() {
		return this->position;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	void setRotation(float degrees, glm::vec3 axis) {
		this->rotationAxis = axis;
		this->rotationDegrees = degrees;
	}

	void setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	string getPath() {
		return (*model).getModelPath();
	}

	Model* getModel() {
		return model;
	}

private:
	glm::vec3 position;

	float rotationDegrees;
	glm::vec3 rotationAxis;

	glm::vec3 scale;

	Model* model;
	Shader* shader;
};
#endif