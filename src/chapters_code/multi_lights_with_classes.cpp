#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <cmath>
#include <exception>
#include <vector>

#include "shader.h" 
#include "texture.h"
#include "transform.h"
#include "flyCamera.h"
#include "light.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"

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
		glm::vec3(0.0f,0.0f,-10.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		90.0f, 0.0f, 45.0f, 10.0f, 0.05f
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

	Shader sourceShaders("/home/iago/Documents/Projects/opengl_tutorial/shaders/vertex.vs", "/home/iago/Documents/Projects/opengl_tutorial/shaders/fragment.fs");
	Shader cubeShaders("/home/iago/Documents/Projects/opengl_tutorial/shaders/light.vs", "/home/iago/Documents/Projects/opengl_tutorial/shaders/light.fs");
	
	Texture cubeTexture(
			{
				"/home/iago/Documents/Projects/opengl_tutorial/textures/container2.png",
				"/home/iago/Documents/Projects/opengl_tutorial/textures/container2_specular.png"	
			},
		   	{"material.diffuse", "material.specular"},
			2, cubeShaders);

	float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
	// VBO, VAO
	unsigned int VBO, cubeVAO;	
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);	
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Attributes
	glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

	// Light VAO
	unsigned int sourceVAO;
	glGenVertexArrays(1, &sourceVAO);
	glBindVertexArray(sourceVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	
	glm::vec3 sourcePos(0.0f, 0.0f, 0.0f);
	glm::vec3 cubePos(1.0f, 1.0f, 1.0f);
	glm::vec3 cubesPos[] = {
		glm::vec3( 1.0f,  1.0f,  1.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};  

	DirectionalLight directionalLight(
		0,
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.2f, -1.0f, 0.3f)	
	);

	std::vector<PointLight> pointLights;
	for (int i = 0; i < 4; i++)
		pointLights.push_back(PointLight(
			i, 
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			pointLightPositions[i],
			1.0f, 0.09f, 0.032f
		));

	SpotLight flashlight(
		0,
		glm::vec3(0.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		camera->getPosition(), camera->getFront(),
		1.0f, 0.09f, 0.032f,
		glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f))
	);

	cubeShaders.setFloat("material.shininess", 64.0f);		
	
	while(!glfwWindowShouldClose(window)) {
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
		cubeShaders.use();
		camera->update(cubeShaders, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");		

		// Update Lights	
		for (auto light : pointLights) light.update(cubeShaders);
		directionalLight.update(cubeShaders);		
		flashlight.setPosition(camera->getPosition());
		flashlight.setDirection(camera->getFront());
		flashlight.update(cubeShaders);	

		// Drawing
		// Cube
		cubeShaders.use();			
		cubeTexture.activate();
		camera->update(cubeShaders, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");		
	
		for (unsigned int i = 0; i < 10; i++) {	
			Transform cubeTransform(&cubeShaders, "model");
			cubeTransform.setTranslate(cubesPos[i]);
			float cubeAngle = (float)glfwGetTime() * glm::radians(20.0f + i);
			cubeTransform.setRotate(cubeAngle * glm::vec3(1.0f, 0.5f, 0.5f));
			cubeTransform.update();		

			cubeShaders.setVec3("viewPos", camera->getPosition());	
			
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}	
		
			
		// Light Source
		sourceShaders.use();
		camera->update(sourceShaders, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");		
		
		for (int i = 0; i < 4; i++) {
			Transform sourceTransform(&sourceShaders, "model");
			sourceTransform.setTranslate(pointLightPositions[i]);
			sourceTransform.setScale(glm::vec3(0.3f, 0.3f, 0.3f));
			float sourceAngle = (float)glfwGetTime() * glm::radians(10.0f);
			sourceTransform.setRotate(sourceAngle * glm::vec3(1.0f, 0.5f, 0.5f));
			sourceTransform.update();	
			
			glBindVertexArray(sourceVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	
		/*
		glm::vec3 cameraPosition = camera->getPosition();		
		std::cout << "Camera: " 
				  << cameraPosition.x << ", "
				  << cameraPosition.y << ", "
				  << cameraPosition.z << std::endl;
		*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &sourceVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

