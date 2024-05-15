#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "model.h"

#include <vector>
#include <string>


class ModelLoader {
public:
	~ModelLoader() {
		for (auto model : loadedModels) {
			delete model;
		}
		loadedModels.clear();
	}

	Model* loadModel(std::string modelPath) {
		// Prevents loading same model twice
		for (size_t i = 0; i < loadedModels.size(); i++)
		{
			if (strcmp((*loadedModels[i]).getModelPath().c_str(), modelPath.c_str()) == 0) {
				printf("Model already loaded.\n");
				return loadedModels[i];
			}
		}
		Model* model = new Model(modelPath);
		loadedModels.push_back(model);
		return model;
	}
private:
	std::vector<Model*> loadedModels;
};

#endif