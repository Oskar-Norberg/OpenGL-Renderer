#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>

#include "shader.h"
#include "mesh.h"

#include <string>
#include <vector>

class Model
{
public:
	Model(std::string const& path);
	~Model();

	void draw(Shader& shader);

	std::string getModelPath();
private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh*>    meshes;
	std::string directory, modelPath;

	void clearTextures();
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
};
#endif

