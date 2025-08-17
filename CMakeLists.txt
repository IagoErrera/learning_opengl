cmake_minimum_required(VERSION 3.10)
project(opengl_tutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(main 
	src/main.cpp 
	thirdparty/glad/src/glad.c 
	thirdparty/stb_image/stb_image.cpp
	
	src/shader/shader.cpp
	src/texture/texture.cpp
	src/transform/transform.cpp
	src/camera/camera.cpp
	src/camera/flyCamera.cpp
)

target_link_libraries(main PRIVATE glfw OpenGL::GL)
target_include_directories(main PRIVATE 
	thirdparty/glad/include
	thirdparty/stb_image
	thirdparty/
)

target_include_directories(main PRIVATE 
	src/shader
	src/texture
	src/transform
	src/camera
)
