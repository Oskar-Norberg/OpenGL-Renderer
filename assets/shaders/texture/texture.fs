#version 330 core

in vec2 TextureCoord;

struct Material{
	sampler2D texture_diffuse1;
	float shininess;
};
uniform Material material;

out vec4 FragColor;

void main(){
	vec4 diffuseTextureFragment = texture(material.texture_diffuse1, TextureCoord);
	FragColor = vec4(diffuseTextureFragment.rgb, 1.0f);
}