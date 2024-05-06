#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TextureCoord;

const int nVertexPrecision = 4;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	float vertexPrecision = pow(2.0f, nVertexPrecision);
	gl_Position.xyz = round(gl_Position.xyz * vertexPrecision) / vertexPrecision;

	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;  
	TextureCoord = aTextureCoord;
}