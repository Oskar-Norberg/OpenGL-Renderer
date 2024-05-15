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
	Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationDegrees, Model* model, Shader* shader);

	void draw();

	glm::vec3 getPosition();

	void setPosition(glm::vec3 position);

	void setRotation(float degrees, glm::vec3 axis);

	void setScale(glm::vec3 scale);

	std::string getPath();

	Model* getModel();

private:
	glm::vec3 position;

	float rotationDegrees;
	glm::vec3 rotationAxis;

	glm::vec3 scale;

	Model* model;
	Shader* shader;
};
#endif