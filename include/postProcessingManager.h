#ifndef POST_PROCESSING_MANAGER_H
#define POST_PROCESSING_MANAGER_H

#include <glad/glad.h>

#include "shader.h"
#include "camera.h"

class PostProcessingManager {
public:
	// TODO: Window width/height should not be set here, renderer and window should be separated. 
	PostProcessingManager(Shader* shader, int windowWidth = 1600, int windowHeight = 900);
	~PostProcessingManager();
	void drawQuad();
	unsigned int getFrameBuffer();
private:
	void setupQuad();
	Shader* shader;
	unsigned int framebuffer, textureColorbuffer, depthStencilRBO, quadVAO, quadVBO;
};

#endif