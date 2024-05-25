#version 330 core

out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D screenTexture;


uniform int strengthExponent;
uniform float strengthMultiplier;
uniform float strengthOffset;

void main(){
	ivec2 screenSize = textureSize(screenTexture, 0);
	float textureMiddleX = screenSize.x/2.0f/screenSize.x;
	float textureMiddleY = screenSize.y/2.0f/screenSize.y;
	vec2 textureMiddle = vec2(textureMiddleX, textureMiddleY);

	float distanceFromCenterOfScreen = distance(TextureCoord, textureMiddle);

	float vignetteStrength = (pow(distanceFromCenterOfScreen, strengthExponent) * strengthMultiplier) + strengthOffset;
	vignetteStrength = clamp(vignetteStrength, 0.0f, 1.0f);
	
	FragColor = texture(screenTexture, TextureCoord);
	FragColor -= vignetteStrength;

	FragColor.a = 1.0f;

}