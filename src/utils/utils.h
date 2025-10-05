#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include "stb_image.h"

#include <string>
#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

#endif
