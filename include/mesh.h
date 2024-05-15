

#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations
#include <assimp/material.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinate;
};

struct Texture {
	unsigned int id;
	// Assimp texture type
	aiTextureType type;
	std::string path;
};

class Mesh {
public:
	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	~Mesh();

	// render the mesh
	void draw(Shader& shader);

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO, VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};
#endif

