#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string>

#include "include/shader.h"
#include "include/object.h"
#include "include/shaderManager.h"


#include "include/pointLight.h"
#include "include/spotlight.h"
#include "include/directionalLight.h"


#include "include/camera.h"

int windowWidth = 1600, windowHeight = 900;
std::string windowName = "Silly little renderer remake 3.0";

glm::mat4 cameraProjectionMat = glm::perspective(glm::radians(45.0f), float(windowWidth) / float(windowHeight), 0.1f, 200.0f);
Camera camera(-90.0f, 0.0f, glm::vec3(0.0f, 0.75f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), cameraProjectionMat);

float lastX, lastY;
bool firstMouse = true;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

GLFWwindow* initializeOpenGL();
void run(GLFWwindow* window);
void quit(GLFWwindow* window);

void setWindShaderUniforms(Shader* shader);

void processInput(GLFWwindow* window);

//Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	GLFWwindow* window = initializeOpenGL();
	run(window);
	quit(window);

	return 0;
}

GLFWwindow* initializeOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		glfwTerminate();
		quit(window);
	}

	glViewport(0, 0, windowWidth, windowHeight);

	// Enable
	// Depth testing
	glEnable(GL_DEPTH_TEST);

	// Setup callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//Lock cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

void run(GLFWwindow* window) {
	ShaderManager shaderManager;

	DirectionalLight sun(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f), 1.0f, 0.09f, 0.032f);
	vector<PointLight*> pointLights;
	vector<Spotlight*> spotlights;

	vector<Object*> opaqueObjects;
	vector<Object*> transparentObjects;

	glm::vec4 backgroundColor(0.4f, 0.4f, 0.4f, 1.0f);

	Shader* textureShader = shaderManager.createShader("assets/shaders/texture/texture.vs", "assets/shaders/texture/texture.fs");
	Shader* multipleLightsShader = shaderManager.createShader("assets/shaders/multipleLights/multipleLights.vs", "assets/shaders/multipleLights/multipleLights.fs");
	Shader* grassShader = shaderManager.createShader("assets/shaders/grass/grass.vs", "assets/shaders/grass/grass.fs");

	(*multipleLightsShader).use();
	(*multipleLightsShader).setFloat("material.shininess", 1.0f);

	Model testModel("assets/models/testScene/testScene.obj");
	Object testObject(glm::vec3(0.0f), &testModel, multipleLightsShader);
	opaqueObjects.push_back(&testObject);

	Model pointLightModel("assets/models/lightBulb/lightBulb.obj");
	PointLight pointlight(glm::vec3(0.0f, 5.0f, 0.0f), &pointLightModel, textureShader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	pointLights.push_back(&pointlight);
	opaqueObjects.push_back(&pointlight);

	PointLight pointlightTwo(glm::vec3(0.0f, 0.75f, 5.0f), &pointLightModel, textureShader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	pointLights.push_back(&pointlightTwo);
	opaqueObjects.push_back(&pointlightTwo);

	Model spotlightModel("assets/models/spotlight/spotlight.obj");
	Spotlight spotlight(glm::vec3(-4.0f, 8.0f, 0.0f), &spotlightModel, textureShader, glm::vec3(0.0f, -1.0f, 0.0f), 12.5f, 15.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	spotlights.push_back(&spotlight);
	opaqueObjects.push_back(&spotlight);

	Model grassModel("assets/models/grass/grass.obj");
	Object grass(glm::vec3(0.0f, 1.0f, -5.0f), &grassModel, grassShader);
	Object grassTwo(glm::vec3(-5.0f, 1.0f, -2.5f), &grassModel, grassShader);
	Object grassThree(glm::vec3(-4.0f, 1.0f, 0.0f), &grassModel, grassShader);
	Object grassFour(glm::vec3(2.0f, 1.0f, -3.0f), &grassModel, grassShader);
	opaqueObjects.push_back(&grass);
	opaqueObjects.push_back(&grassTwo);
	opaqueObjects.push_back(&grassThree);
	opaqueObjects.push_back(&grassFour);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		printf("%f ms\n", currentFrame - lastFrame);
		printf("%f fps\n", 1 / (currentFrame - lastFrame));
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderManager.setCameraMatrices(&camera);

		pointlight.setPosition(glm::vec3(sin(currentFrame * 2.0f) * 5.0f, 0.0f, 0.0f));

		shaderManager.setLights(sun, pointLights, spotlights);

		for (size_t i = 0; i < opaqueObjects.size(); i++)
		{
			(*opaqueObjects[i]).draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void quit(GLFWwindow* window) {
	printf("yea you should probably write me later");
}

void setWindShaderUniforms(Shader* shader){
	(*shader).use();
	(*shader).setFloat("time", float(glfwGetTime()));
	(*shader).setFloat("windSpeed", 1.0f);
	(*shader).setFloat("windStrength", 0.5f);
	
}

void processInput(GLFWwindow* window)
{
	float movementSpeed = 10.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	glm::vec3 direction(0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		direction.z -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		direction.x -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		direction.z += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		direction.x += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		direction.y += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		direction.y -= 1.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.setSprint(true);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera.setSprint(false);

	if (glm::length(direction) > 0.0f)
		camera.handleKeyboard(direction, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.handleMouseMovement(xOffset, yOffset);
}