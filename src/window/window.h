#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <exception>

#define WINDOW_HEIGHT 600.0f
#define WINDOW_WIDTH  800.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* initWindow(
	void (*mouseCallback)(GLFWwindow* window, double xpos, double ypos),
	void (*scrollCalback)(GLFWwindow* window, double xoffset, double yoffset)
);

#endif
