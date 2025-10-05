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
#include <string>

#include "window.h"
#include "shader.h" 
#include "transform.h"
#include "flyCamera.h"
#include "light.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "model.h"

#define WINDOW_HEIGHT 600.0f
#define WINDOW_WIDTH  800.0f

#define PATH (std::string)"/home/iago/Documents/Projects/opengl_tutorial/"

FlyCamera* camera = nullptr;

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

void checkGLErrors() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
}

int main() {
	GLFWwindow* window = initWindow(mouseCallback, scrollCalback);

	Shader shader(
		(PATH + (std::string)"shaders/model.vs").c_str(),
		(PATH + (std::string)"shaders/model.fs").c_str()
	);
    Model model((PATH + (std::string)"resources/models/backpack/backpack.obj").c_str());		
	camera = new FlyCamera(
		glm::vec3(0.0f, 0.0f, 3.0f),  
		glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f),  
		-90.0f, 0.0f, 45.0f,          
		2.5f, 0.1f                    
	);

	shader.use();
	DirectionalLight directionalLight(
		0, glm::vec3(0.1f), glm::vec3(0, 0, 0.8f), glm::vec3(0.0f), glm::vec3(1.0f)
	);

	PointLight pointLight(
		0,
		glm::vec3(0.1f), glm::vec3(0.8f, 0, 0), glm::vec3(0), glm::vec3(-2.0f),
		1, 0.022, 0.020
	);

	SpotLight spotLight(
		0,
		glm::vec3(0.0f), glm::vec3(0.8f), glm::vec3(0),
		camera->getPosition(), camera->getFront(),
		1, 0.22, 0.20, glm::radians(12.5f), glm::radians(15.0f)
	);

	shader.setInt("n_directional_lights", 1);
	shader.setInt("n_point_lights", 1);
	shader.setInt("n_spot_lights", 1);
	shader.setInt("material.shininess", 32);

	while(!glfwWindowShouldClose(window)) {
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.use();
		
		camera->update(shader, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");				
		
		spotLight.setPosition(camera->getPosition());
		spotLight.setDirection(camera->getFront());
		
		directionalLight.update(shader);
		pointLight.update(shader);	
		spotLight.update(shader);	

		Transform transform(&shader, "model");
		transform.setTranslate(glm::vec3(0.0f));
		transform.setScale(glm::vec3(1.0f));
		transform.update();
		
		model.draw(shader);

		checkGLErrors();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete camera;

	glfwTerminate();

	return 0;
}

