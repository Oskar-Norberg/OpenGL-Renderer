#include "../include/object.h"

Object::Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader) {
	this->position = position;

	this->scale = scale;

	this->rotationAxis = rotationAxis;
	this->rotationDegrees = rotationDegrees;

	this->model = model;
	this->shader = shader;
}

void Object::draw() {
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

glm::vec3 Object::getPosition() {
	return this->position;
}

void Object::setPosition(glm::vec3 position) {
	this->position = position;
}

void Object::setRotation(float degrees, glm::vec3 axis) {
	this->rotationAxis = axis;
	this->rotationDegrees = degrees;
}

void Object::setScale(glm::vec3 scale) {
	this->scale = scale;
}

std::string Object::getPath() {
	return (*model).getModelPath();
}

Model* Object::getModel() {
	return model;
}
