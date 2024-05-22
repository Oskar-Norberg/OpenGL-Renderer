#include "../include/postProcessingManager.h"
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
