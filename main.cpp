#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "include/shader.h"
#include "include/object.h"
#include "include/scene.h"
#include "include/lights.h"
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
	// Transparency (Blending)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Setup callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//Lock cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

void run(GLFWwindow* window) {
	Scene scene;

	scene.setSun(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.75f));
	//scene.setSun(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f));

	Shader* textureShader = scene.createShader("assets/shaders/texture/texture.vs", "assets/shaders/texture/texture.fs");
	//Shader* vertexWobble = scene.createShader("assets/shaders/vertexWobble/vertexWobble.vs", "assets/shaders/multipleLights/multipleLights.fs");
	Shader* multipleLightsShader = scene.createShader("assets/shaders/multipleLights/multipleLights.vs", "assets/shaders/multipleLights/multipleLights.fs");
	(*multipleLightsShader).use();
	(*multipleLightsShader).setFloat("material.shininess", 1.0f);

	Shader* grassShader = scene.createShader("assets/shaders/grass/grass.vs", "assets/shaders/grass/grass.fs");
	(*grassShader).use();
	(*grassShader).setFloat("windSpeed", 1.0f);
	(*grassShader).setFloat("windStrength", 0.5f);

	Object* testSceneObject = scene.createObject(false, "assets/models/testScene/testScene.obj", glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), 0.0f, multipleLightsShader);

	Object* grassObject = scene.createObject(false, "assets/models/grass/grass.obj", glm::vec3(0.0f, 1.0f, -5.0f), glm::vec3(0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, grassShader);
	Object* grassObjectTwo = scene.createObject(false, "assets/models/grass/grass.obj", glm::vec3(-5.0f, 1.0f, -2.5f), glm::vec3(1.2f), glm::vec3(0.0f, 1.0f, 0.0f), 35.0f, grassShader);
	Object* grassObjectThree = scene.createObject(false, "assets/models/grass/grass.obj", glm::vec3(-4.0f, 1.0f, 0.0f), glm::vec3(0.9f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, grassShader);
	Object* grassObjectFour = scene.createObject(false, "assets/models/grass/grass.obj", glm::vec3(2.0f, 1.0f, -3.0f), glm::vec3(0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 50.0f, grassShader);

	Object* cirno = scene.createObject(false, "assets/models/cirnoFumo/cirnoFumo.obj", glm::vec3(0.0f, 0.0f, -6.0f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -55.0f, multipleLightsShader);
	Object* gman = scene.createObject(false, "assets/models/gman/gman.obj", glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, multipleLightsShader);

	Object* windowObj = scene.createObject(true, "assets/models/window/window.obj", glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, multipleLightsShader);
	Object* windowObjTwo = scene.createObject(true, "assets/models/window/window.obj", glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, multipleLightsShader);

	PointLight* pointlight = scene.createPointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f), glm::vec3(0.2f), 1.0f, 0.35f, 0.44f);
	//PointLight* pointlightTwo = scene.createPointLight(glm::vec3(0.0f, 0.75f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	Spotlight* spotlight = scene.createSpotlight(glm::vec3(-4.0f, 8.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), 12.5f, 15.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

	Shader* postProcessingShader = scene.createShader("assets/shaders/postProcessing/postProcess.vs", "assets/shaders/postProcessing/drawTexture/drawTexture.fs");
	
	scene.createPostProcessingEffect(postProcessingShader);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		printf("%f ms\n", currentFrame - lastFrame);
		printf("%f fps\n", 1 / (currentFrame - lastFrame));
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// Custom shaders
		//(*gman).setPosition((*gman).getPosition() + glm::vec3(sin(currentFrame/10.0f) * 0.001f, 0.0f, 0.0f));
		//(*pointlight).position.x = sin(currentFrame) * 10.0f;
		//scene.setLights();
		(*grassShader).use();
		(*grassShader).setFloat("time", float(glfwGetTime()));

		scene.setLights();

		scene.draw(&camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void quit(GLFWwindow* window) {
	glfwDestroyWindow(window);
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

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.setCrouch(true);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
		camera.setCrouch(false);

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