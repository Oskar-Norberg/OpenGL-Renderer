#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

uniform float time;

uniform float windSpeed;
uniform float windStrength;

layout (std140) uniform ViewProjectionMatrices
{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;

out vec2 TextureCoord;

void main()
{
	vec4 screenSpacePosition = projection * view * model * vec4(aPos, 1.0f);
	screenSpacePosition += sin(time * windSpeed) * (aPos.y + 1.0f) * windStrength;

	gl_Position = screenSpacePosition;
	TextureCoord = aTextureCoord;
}