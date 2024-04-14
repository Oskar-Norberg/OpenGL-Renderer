#version 330 core

struct Material{
	sampler2D texture_diffuse1;
};
uniform Material material;

in vec2 TextureCoord;

out vec4 FragColor;

void main(){
	vec4 textureFrag = texture(material.texture_diffuse1, TextureCoord);
	if (textureFrag.a < 0.1f){
		discard;
	}
	FragColor = textureFrag;
}