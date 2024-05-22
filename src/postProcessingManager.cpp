#include "../include/postProcessingManager.h"

// Find some way to make this class agnostic to OpenGL. Use object.h somehow

// Quad Vertices - Might profit from being saved elsewhere, create a meshdata.h perhaps
// Could also hold other common mesh types vertices

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};

PostProcessingManager::PostProcessingManager(Shader* shader, int windowWidth, int windowHeight) {
	this->shader = shader;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &textureColorbuffer);
	glGenRenderbuffers(1, &depthStencilRBO);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Set color texture buffer properties
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set Depth/Stencil RBO properties
	glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);

	// Bind color texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// Bind depth/stencil RBO to framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("ERROR - Framebuffer not created sucessfully\n");
	}
	else {
		printf("Framebuffer created sucessfully\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	setupQuad();
}

PostProcessingManager::~PostProcessingManager() {
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteTextures(1, &textureColorbuffer);
	glDeleteRenderbuffers(1, &depthStencilRBO);
}

void PostProcessingManager::setupQuad() {
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	// Texture coord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void PostProcessingManager::drawQuad() {
	glBindVertexArray(quadVAO);
	shader->use();
	shader->setInt("screenTexture", 0);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

unsigned int PostProcessingManager::getFrameBuffer() {
	return framebuffer;
}