#version 330 core

out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D screenTexture;

const ivec2 textureSamplerOffsets[3] = ivec2[](ivec2(5, 5), ivec2(-5, -10), ivec2(5, -5));


void main(){
	// Fix a proper way to set screen size
	ivec2 screenSize = textureSize(screenTexture, 0);
	float textureMiddleX = screenSize.x/2.0f/screenSize.x;
	float textureMiddleY = screenSize.y/2.0f/screenSize.y;
	vec2 textureMiddle = vec2(textureMiddleX, textureMiddleY);

	float distanceFromCenterOfScreen = distance(TextureCoord, textureMiddle);
	for (int i = 0; i < 3; i++){
		ivec2 offset = ivec2(textureSamplerOffsets[i] * distanceFromCenterOfScreen);
		FragColor[i] = textureOffset(screenTexture, TextureCoord, offset)[i];
	}
	FragColor.a = 1.0f;

}