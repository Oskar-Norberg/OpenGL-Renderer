#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

layout (std140) uniform ViewProjectionMatrices
{
    mat4 view;
    mat4 projection;
	vec3 viewPosition;
};
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out vec2 TextureCoord;
out vec3 viewPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormal;  
	TextureCoord = aTextureCoord;
	viewPos = viewPosition;
}