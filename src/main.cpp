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
#include "cube.h"
#include "texture2d.h"

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

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Shader shader(
		(PATH + (std::string)"shaders/model.vs").c_str(),
		(PATH + (std::string)"shaders/model.fs").c_str()
	);

	Shader outline_shader(
		(PATH + (std::string)"shaders/model.vs").c_str(),
		(PATH + (std::string)"shaders/outline.fs").c_str()
	);
	
	Texture2D container_texture(
		{
			PATH + (std::string)"resources/textures/container2.png",
			PATH + (std::string)"resources/textures/container2_specular.png"
		},
		{"material.diffuse", "material.specular"}, 2, shader
	);	

	Texture2D marble_texture(
		{
			PATH + (std::string)"resources/textures/cracked-cement.jpg",
			PATH + (std::string)"resources/textures/cracked-cement.jpg"
		},
		{"material.diffuse", "material.specular"}, 2, shader
	);
	
	camera = new FlyCamera();
	camera->setPosition(glm::vec3(0,3,0));
	camera->setYaw(30);

	Cube ground = Cube(&shader, &marble_texture);
	ground.transform.setTranslate(glm::vec3(0,0,0));
	ground.transform.setScale(glm::vec3(20,1,20));

	Cube container_1 = Cube(&shader, &container_texture);
	container_1.transform.setTranslate(glm::vec3(-1,2,-1.5));
	Cube container_2 = Cube(&shader, &container_texture);
	container_2.transform.setTranslate(glm::vec3(2,3,3));
	
	PointLight pLight(
		0, glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.3f), glm::vec3(0, 2, 0),
		1, 0.022, 0.002
	);
	
	std::vector<Shader> shaders{shader, outline_shader};	

	for (auto s : shaders) {
		s.setInt("n_point_lights", 1);
		s.setFloat("material.shininess", 32);
	} 

	while(!glfwWindowShouldClose(window)) {	
		processInput(window);
		
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		for (auto s : shaders) {
			s.use();
			camera->update(s, WINDOW_WIDTH/WINDOW_HEIGHT, "view", "projection");				
			s.setVec3("viewPos", camera->getPosition());
			pLight.update(s);
		}
		
		glStencilMask(0x00);
		ground.draw();
		
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
		container_1.draw();
		container_2.draw();
		
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
		container_1.transform.setScale(glm::vec3(1.1,1.1,1.1));	
		container_1.draw(&outline_shader);
		container_2.transform.setScale(glm::vec3(1.1,1.1,1.1));	
		container_2.draw(&outline_shader);
		glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
		container_1.transform.setScale(glm::vec3(1,1,1));	
		container_2.transform.setScale(glm::vec3(1,1,1));	

		checkGLErrors();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete camera;

	glfwTerminate();

	return 0;
}

