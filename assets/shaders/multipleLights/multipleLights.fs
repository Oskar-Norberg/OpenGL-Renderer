#version 330 core
#define MAX_SPOTLIGHTS 10
#define MAX_POINT_LIGHTS 10

struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular2;
	float shininess;
};

struct Spotlight{
	vec3 position;
	float cutoff;
	vec3 direction;
	float outerCutoff;
	vec3 ambient;
	float constant;
	vec3 diffuse;
    float linear;
	vec3 specular;
    float quadratic;
};

struct PointLight{
	vec3 position;
	float constant;
	vec3 ambient;
    float linear;
	vec3 diffuse;
    float quadratic;
	vec3 specular;
};

struct DirectionalLight{
	vec3 direction;
	float constant;
	vec3 ambient;
    float linear;
	vec3 diffuse;
    float quadratic;
	vec3 specular;

};

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 viewPos;

uniform Material material;

uniform Spotlight spotlights[MAX_SPOTLIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight directionalLight;

uniform int nrOfSpotlights;
uniform int nrOfPointLights;

out vec4 FragColor;

vec3 calcDirectionalLight(DirectionalLight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment);
vec3 calcPointLight(PointLight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment);
vec3 calcSpotlight(Spotlight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment);

float calcLightAttenuation(float constant, float linear, float quadratic, float distance);

void main(){
	vec3 normalizedNormal = normalize(Normal);

	vec4 diffuseTextureFragment = texture(material.texture_diffuse1, TextureCoord);
	vec4 specularTextureFragment = texture(material.texture_specular1, TextureCoord);

	// Directional light (sun)
	vec3 result = calcDirectionalLight(directionalLight, normalizedNormal, diffuseTextureFragment, specularTextureFragment);

	// Point Lights
	for (int i = 0; i < nrOfPointLights; i++)
	{
		result += calcPointLight(pointLights[i], normalizedNormal, diffuseTextureFragment, specularTextureFragment);
	}
	// Spotlights
	for (int i = 0; i < nrOfSpotlights; i++)
	{
		result += calcSpotlight(spotlights[i], normalizedNormal, diffuseTextureFragment, specularTextureFragment);
	}

	// Test if color is clipping (above floating point buffer)
	/*
	if (result.r < 1.0f || result.g < 1.0f || result.b < 1.0f){
		result = vec3(1.0f, 0.0f, 0.0f);
	}
	*/
	
	FragColor = vec4(result, diffuseTextureFragment.a);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment){
	vec3 lightDirection = normalize(-light.direction);

	// Ambient light
	vec3 ambient = light.ambient * diffuseTextureFragment.rgb;

	// Diffuse light
	float diffuseStrength = max(dot(normalizedNormal, lightDirection), 0.0f);
	vec3 diffuse = diffuseTextureFragment.rgb * diffuseStrength * light.diffuse;

	// Specular light
	vec3 viewingDirection = normalize(viewPos - FragPos);
	vec3 reflectedLight = reflect(-lightDirection, normalizedNormal);
	float specularStrength = max(dot(viewingDirection, reflectedLight), 0.0f);
	specularStrength  = pow(specularStrength, material.shininess);
	vec3 specular = specularTextureFragment.rgb * specularStrength * light.specular;

	// Result
	vec3 result = ambient + diffuse + specular;

	return result;
}

vec3 calcPointLight(PointLight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment){
	vec3 lightDirection = normalize(light.position - FragPos);

	// Ambient light
	vec3 ambient = diffuseTextureFragment.rgb * light.ambient;

	// Diffuse light
	float diffuseStrength = max(dot(normalizedNormal, lightDirection), 0.0f);
	vec3 diffuse = diffuseTextureFragment.rgb * diffuseStrength * light.diffuse;

	// Specular light
	vec3 viewingDirection = normalize(viewPos - FragPos);
	vec3 reflectedLight = reflect(-lightDirection, normalizedNormal);
	float specularStrength = max(dot(viewingDirection, reflectedLight), 0.0f);
	specularStrength  = pow(specularStrength, material.shininess);
	vec3 specular = specularTextureFragment.rgb * specularStrength * light.specular;

	// Result
	vec3 result = ambient + diffuse + specular;

	return result;
}

vec3 calcSpotlight(Spotlight light, vec3 normalizedNormal, vec4 diffuseTextureFragment, vec4 specularTextureFragment){
	float lengthFromLight = length(light.position - FragPos);
	vec3 lightDirection = normalize(light.position - FragPos);

	//Attenuation
	float attenuation = calcLightAttenuation(light.constant, light.linear, light.quadratic, lengthFromLight);
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	// Ambient light
	vec3 ambient = light.ambient * diffuseTextureFragment.rgb;

	// Diffuse light
	vec3 diffuse = diffuseTextureFragment.rgb * light.diffuse;

	// Specular light
	vec3 viewingDirection = normalize(viewPos - FragPos);
	vec3 reflectedLight = reflect(-lightDirection, normalizedNormal);
	float specularStrength = max(dot(viewingDirection, reflectedLight), 0.0f);
	specularStrength  = pow(specularStrength, material.shininess);
	vec3 specular = specularTextureFragment.rgb * specularStrength * light.specular;

	// Result
	vec3 result = ambient + diffuse + specular;
	result *= intensity * attenuation;

	return result;
}

float calcLightAttenuation(float constant, float linear, float quadratic, float distance){
	return 1.0f/(constant + linear * distance + quadratic * distance * distance);
}