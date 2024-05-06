#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

layout (std140) uniform ViewProjectionMatrices
{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;

out vec2 TextureCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TextureCoord = aTextureCoord;
}