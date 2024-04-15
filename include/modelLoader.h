#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "model.h"

using std::vector;
using std::string;

class ModelLoader {
public:
	Model* loadModel(std::string modelPath) {
		Model* model = new Model(modelPath);
		loadedModels.push_back(model);
		return model;
	}
private:
	vector<Model*> loadedModels;
};

#endif