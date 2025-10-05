cmake_minimum_required(VERSION 3.10)
project(opengl_tutorial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
cmake_policy(SET CMP0072 NEW)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

add_executable(main 
	src/main.cpp 
	thirdparty/glad/src/glad.c 
	thirdparty/stb_image/stb_image.cpp
	
	src/shader/shader.cpp
	src/texture2d/texture2d.cpp
	src/transform/transform.cpp
	src/camera/camera.cpp
	src/camera/flyCamera.cpp
	src/lights/light.cpp
	src/lights/directionalLight.cpp
	src/lights/pointLight.cpp
	src/lights/spotLight.cpp
	src/mesh/mesh.cpp
	src/model/model.cpp
	src/utils/utils.cpp
	src/window/window.cpp
	src/cube/cube.cpp
)

target_link_libraries(main PRIVATE 
	glfw
	OpenGL::GL
	assimp
)

target_include_directories(main PRIVATE 
	thirdparty/glad/include
	thirdparty/stb_image
	thirdparty/
)

target_include_directories(main PRIVATE 
	src/shader
	src/texture2d
	src/transform
	src/camera
	src/lights
	src/mesh
	src/model
	src/utils
	src/window
	src/cube
)
