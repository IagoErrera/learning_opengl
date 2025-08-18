#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <exception>

#include "shader.h" 
#include "texture.h"
#include "transform.h"
#include "flyCamera.h"

#define WINDOW_HEIGHT 600.0f
#define WINDOW_WIDTH  800.0f

FlyCamera* camera = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0,0,width, height);
}

void processInput(GLFWwindow* window) {
	static float lastFrame = glfwGetTime();
	
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (camera != nullptr) camera->movementHandle(window, deltaTime);
	
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (camera != nullptr) camera->mouseHandle(xpos, ypos);	
}

void scrollCalback(GLFWwindow* window, double xoffset, double yoffset) {
	if (camera != nullptr) camera->scrollHandle(yoffset);
}

GLFWwindow* initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	camera = new FlyCamera(
		glm::vec3(0.0f,0.0f,10.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 45.0f, 10.0f, 0.05f
	);

	// Capture Mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide Cursor
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCalback);

	glEnable(GL_DEPTH_TEST); // Z-Buffer

	return window;
}

int main() {
	GLFWwindow* window = initWindow();

	Shader normalShaders("/home/iago/Documents/Projects/opengl_tutorial/shaders/vertex.vs", "/home/iago/Documents/Projects/opengl_tutorial/shaders/fragment.fs");
	Shader lightShaders("/home/iago/Documents/Projects/opengl_tutorial/shaders/vertex.vs", "/home/iago/Documents/Projects/opengl_tutorial/shaders/light.fs");

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// VBO, VAO
	unsigned int VBO, VAO;	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);	
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	
	// Light VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);	

	// Texture
	Texture texture(
		{
			"/home/iago/Documents/Projects/opengl_tutorial/textures/container.jpg",
			"/home/iago/Documents/Projects/opengl_tutorial/textures/wall.jpg",
		},
		{"texture1", "texture2"}, 2, lightShaders
	);


	lightShaders.use();
	lightShaders.setVec3("objectColor", glm::vec3(1.0, 0.5f, 0.31f));
	lightShaders.setVec3("lightColor", glm::vec3(1.0, 1.0f, 1.0f));

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 cubePos(0.0f, 0.0f, 0.0f);

	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		texture.activate();

		camera->update(lightShaders, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");		

		Transform lightTransform(&lightShaders, "model");
		lightTransform.translate(lightPos);
		float lightAngle = (float)glfwGetTime() * glm::radians(20.0f);
		lightTransform.rotate(lightAngle * glm::vec3(1.0f, 0.5f, 0.5f));
		lightTransform.update();
		lightShaders.use();	
		
		lightShaders.use();			
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
			
		camera->update(normalShaders, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");		
		
		Transform normalTransform(&normalShaders, "model");
		normalTransform.translate(cubePos);
		float normalAngle = (float)glfwGetTime() * glm::radians(10.0f);
		normalTransform.rotate(normalAngle * glm::vec3(1.0f, 0.5f, 0.5f));
		normalTransform.update();
		normalShaders.use();			
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

