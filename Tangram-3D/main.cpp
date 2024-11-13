// Code adapted from www.learnopengl.com, www.glfw.org

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

// Camera

glm::vec3 cameraPos = glm::vec3(0.0f, -0.25f, 5.0f);    // Moved down slightly and back
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  // Looking slightly downward
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);       // Standard up vector

// Light attributes
glm::vec3 lightPos(1.0f, 0.0f, 1.0f);

// The MAIN function, from here we start the application and run the game loop
int main(void)
{
	//++++create a glfw window+++++++++++++++++++++++++++++++++++++++
	GLFWwindow* window;

	if (!glfwInit()) //Initialize the library
		return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//Make the window's context current

	//++++Initialize GLEW to setup the OpenGL Function pointers+++++++
	glewExperimental = GL_TRUE;
	glewInit();

	//++++Define the viewport dimensions++++++++++++++++++++++++++++
	glViewport(0, 0, HEIGHT, HEIGHT);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// First Triangle (Top)
	GLfloat firsttriangle[] = {
		// Front triangle
		-1.0f,  1.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		 // Back triangle
		 -1.0f,  1.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		  1.0f,  1.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		  // Left side
		  -1.0f,  1.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		  -1.0f,  1.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		  -1.0f,  1.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		  // Right side
		   0.0f,  0.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		   1.0f,  1.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		   1.0f,  1.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		   1.0f,  1.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		   // Top face
		   -1.0f,  1.0f,  0.25f,   0.0f,  1.0f,  0.0f,
		   -1.0f,  1.0f, -0.25f,   0.0f,  1.0f,  0.0f,
			1.0f,  1.0f,  0.25f,   0.0f,  1.0f,  0.0f,
			1.0f,  1.0f,  0.25f,   0.0f,  1.0f,  0.0f,
			1.0f,  1.0f, -0.25f,   0.0f,  1.0f,  0.0f,
		   -1.0f,  1.0f, -0.25f,   0.0f,  1.0f,  0.0f
	};

	// Second Triangle (Left)
	GLfloat secondtriangle[] = {
		// Front face
		-1.0f,  1.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		-1.0f, -1.0f,  0.25f,   0.0f,  0.0f,  1.0f,
		// Back face
		-1.0f,  1.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -0.25f,   0.0f,  0.0f, -1.0f,
		// Left edge
		-1.0f,  1.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.25f,  -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -0.25f,  -1.0f,  0.0f,  0.0f,
		// Upper right edge
		-1.0f,  1.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		// Lower right edge
		 0.0f,  0.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -0.25f,   1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.25f,   1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  0.25f,   1.0f,  0.0f,  0.0f
	};

	// Third Triangle (Upper Right)
	GLfloat thirdtriangle[] = {
		// Front face
		1.0f,  1.0f,  0.25f,    0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.25f,    0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.25f,    0.0f,  0.0f,  1.0f,
		// Back face
		1.0f,  1.0f, -0.25f,    0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.25f,    0.0f,  0.0f, -1.0f,
		1.0f,  0.0f, -0.25f,    0.0f,  0.0f, -1.0f,
		// Right edge
		1.0f,  1.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		// Upper left edge
		1.0f,  1.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.25f,    1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.25f,    1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		// Lower left edge
		0.5f,  0.5f,  0.25f,    1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.25f,    1.0f,  0.0f,  0.0f,
		1.0f,  0.0f, -0.25f,    1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.25f,    1.0f,  0.0f,  0.0f
	};


	GLfloat square[] = {
		// Front face (2 triangles)
		// Triangle 1
		0.0f,  0.0f,   0.25f,   0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,   0.25f,   0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,   0.25f,   0.0f,  0.0f,  1.0f,
		// Triangle 2
		0.0f,  0.0f,   0.25f,   0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,   0.25f,   0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,   0.25f,   0.0f,  0.0f,  1.0f,

		// Back face (2 triangles)
		// Triangle 1
		0.0f,  0.0f,  -0.25f,   0.0f,  0.0f, -1.0f,
		1.0f,  0.0f,  -0.25f,   0.0f,  0.0f, -1.0f,
		0.5f,  0.5f,  -0.25f,   0.0f,  0.0f, -1.0f,
		// Triangle 2
		0.0f,  0.0f,  -0.25f,   0.0f,  0.0f, -1.0f,
		0.5f, -0.5f,  -0.25f,   0.0f,  0.0f, -1.0f,
		1.0f,  0.0f,  -0.25f,   0.0f,  0.0f, -1.0f,

		// Top edge face (2 triangles)
		// Triangle 1
		0.5f,  0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  -0.25f,   1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		// Triangle 2
		1.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  -0.25f,   1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,

		// Bottom edge face (2 triangles)
		// Triangle 1
		0.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  -0.25f,   1.0f,  0.0f,  0.0f,
		// Triangle 2
		0.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  -0.25f,   1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,

		// Left edge face (2 triangles)
		// Triangle 1
		0.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		// Triangle 2
		0.5f,  0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  -0.25f,   1.0f,  0.0f,  0.0f,

		// Right edge face (2 triangles)
		// Triangle 1
		1.0f,  0.0f,   0.25f,   1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		// Triangle 2
		0.5f, -0.5f,   0.25f,   1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  -0.25f,   1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  -0.25f,   1.0f,  0.0f,  0.0f
	};

	// TODO Scale from -0.25 to -0.35 for Back VErtices


	GLfloat fourthtriangle[]{
		// Front face
		0.0f, 0.0f, 0.25f,     0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.25f,     0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.25f,   0.0f, 0.0f, 1.0f,

		// Back face
		0.0f, 0.0f, -0.25f,    0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.25f,    0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.25f,  0.0f, 0.0f, -1.0f,

		// Right side face
		0.5f, -0.5f, 0.25f,     1.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.25f,    1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -0.25f,    1.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.25f,     1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.25f,     1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -0.25f,    1.0f, -1.0f, 0.0f,

		// Left side face
		0.0f, 0.0f, 0.25f,     -1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -0.25f,    -1.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.25f,  -1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.25f,     -1.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.25f,   -1.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.25f,  -1.0f, -1.0f, 0.0f,

		// Bottom face
		-0.5f, -0.5f, 0.25f,   0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.25f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.25f,   0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.25f,   0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.25f,    0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.25f,   0.0f, -1.0f, 0.0f
	};

	GLfloat fifthtriangle[] = {
		// Front face
		1.0f, 0.0f, 0.25f,      0.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 0.25f,     0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.25f,     0.0f, 0.0f, 1.0f,

		// Back face
		1.0f, 0.0f, -0.25f,     0.0f, 0.0f, -1.0f,
		0.0f, -1.0f, -0.25f,    0.0f, 0.0f, -1.0f,
		1.0f, -1.0f, -0.25f,    0.0f, 0.0f, -1.0f,


		1.0f, 0.0f, 0.25f,      1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -0.25f,     1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.25f,    1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.25f,      1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.25f,     1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.25f,    1.0f, 0.0f, 0.0f,


		1.0f, 0.0f, 0.25f,      -1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -0.25f,     -1.0f, 1.0f, 0.0f,
		0.0f, -1.0f, -0.25f,    -1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.25f,      -1.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.25f,     -1.0f, 1.0f, 0.0f,
		0.0f, -1.0f, -0.25f,    -1.0f, 1.0f, 0.0f,

		// Bottom face
		0.0f, -1.0f, 0.25f,     0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.25f,     0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.25f,     0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f
	};

	GLfloat parallelogram[] = {
		// Front face
		-1.0f, -1.0f,  0.25f,    0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.25f,    0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.25f,    0.0f, 0.0f,  1.0f,
		-1.0f, -1.0f,  0.25f,    0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.25f,    0.0f, 0.0f,  1.0f,
		 0.0f, -1.0f,  0.25f,    0.0f, 0.0f,  1.0f,

		 // Back face
		 -1.0f, -1.0f, -0.25f,    0.0f, 0.0f, -1.0f,
		  0.0f, -1.0f, -0.25f,    0.0f, 0.0f, -1.0f,
		  0.5f, -0.5f, -0.25f,    0.0f, 0.0f, -1.0f,
		 -1.0f, -1.0f, -0.25f,    0.0f, 0.0f, -1.0f,
		  0.5f, -0.5f, -0.25f,    0.0f, 0.0f, -1.0f,
		 -0.5f, -0.5f, -0.25f,    0.0f, 0.0f, -1.0f,

		 // Top edge
		 -0.5f, -0.5f,  0.25f,    0.0f, 1.0f, 0.0f,
		  0.5f, -0.5f,  0.25f,    0.0f, 1.0f, 0.0f,
		  0.5f, -0.5f, -0.25f,    0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f,  0.25f,    0.0f, 1.0f, 0.0f,
		  0.5f, -0.5f, -0.25f,    0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, -0.25f,    0.0f, 1.0f, 0.0f,


		 -1.0f, -1.0f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		 -1.0f, -1.0f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		 -1.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,


		  0.5f, -0.5f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		  0.5f, -0.5f,  0.25f,    0.0f, -1.0f, 0.0f,
		  0.0f, -1.0f, -0.25f,    0.0f, -1.0f, 0.0f,
		  0.5f, -0.5f, -0.25f,    0.0f, -1.0f, 0.0f,

		  // Left slant
		  -1.0f, -1.0f,  0.25f,    -1.0f, 0.0f, 0.0f,
		  -0.5f, -0.5f,  0.25f,    -1.0f, 0.0f, 0.0f,
		  -0.5f, -0.5f, -0.25f,    -1.0f, 0.0f, 0.0f,
		  -1.0f, -1.0f,  0.25f,    -1.0f, 0.0f, 0.0f,
		  -0.5f, -0.5f, -0.25f,    -1.0f, 0.0f, 0.0f,
		  -1.0f, -1.0f, -0.25f,    -1.0f, 0.0f, 0.0f
	};
	// Scale from 0.25 to 0.1f


	// First, set the container's VAO (and VBO)
	GLuint VBOs[7], VAOs[7], EBOs[2];
	glGenVertexArrays(7, VAOs); // the address-of operator (&) is not needed here, as the array name is a pointer type
	glGenBuffers(7, VBOs);
	glGenBuffers(2, EBOs);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firsttriangle), firsttriangle, GL_STATIC_DRAW);

	glBindVertexArray(VAOs[0]);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//second triangle 

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondtriangle), secondtriangle, GL_STATIC_DRAW);

	glBindVertexArray(VAOs[1]);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//third triangle 

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thirdtriangle), thirdtriangle, GL_STATIC_DRAW);

	glBindVertexArray(VAOs[2]);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Square setup
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	//fourth triangle 
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fourthtriangle), fourthtriangle, GL_STATIC_DRAW);

	glBindVertexArray(VAOs[4]);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	 

	//fifth triangle 
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fifthtriangle), fifthtriangle, GL_STATIC_DRAW);

	glBindVertexArray(VAOs[5]);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// para setup
	glBindVertexArray(VAOs[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogram), parallelogram, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Build and compile our shader program
	GLuint shaderProgram = initShader("vert.glsl", "frag.glsl");

	GLfloat startTime = (GLfloat)glfwGetTime();			// Start time of the program

	GLfloat animationDuration = 1.0f;					// Default animation duration
	GLfloat delayAnimationTime = 1.5f;					// Delay time between animations

	bool hasTransformed = false;						// Whether the Tangram has transformed

	GLfloat flipParallelogramStartTime = 1.0f;
	bool flipParallelogram = false;						// Animation on whether parallelogram is flipped


	GLfloat time = (GLfloat)glfwGetTime();
	GLfloat duration = 0.4f;
	GLfloat rotate_angle = (GLfloat)glm::radians(0.0f);
	GLfloat current_angle = 0.0f;

	// Animations
	GLfloat animationStartTime = (GLfloat)glfwGetTime() + 1.5f;
	GLfloat animationTransitionDelay = (GLfloat)glfwGetTime();
	bool firstPhaseCompleted = false;
	bool secondPhaseCompleted = false;
	bool thirdPhaseCompleted = false;

	GLfloat explosionFactor = -1.0f;
	bool should_explode = false;

	GLfloat explosionStartTime = 0.0f;
	GLfloat explosionDuration = 1.0f;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		bool play_animation = /*((GLfloat)glfwGetTime() >= animationTransitionDelay) */false;

		glClearColor(0.5, 0.5, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);

		GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

		GLfloat currentTime = (GLfloat)glfwGetTime();
		GLfloat elapsedTime = currentTime - startTime;

		bool transitionStarted = elapsedTime >= delayAnimationTime;
	/*	std::cout << "ELapsed time: " << elapsedTime << std::endl;*/
		GLfloat animationProgress = (currentTime - (startTime + delayAnimationTime)) * duration;
		if (animationProgress > 1.0f && !hasTransformed) {
			hasTransformed = true;
			flipParallelogramStartTime = (GLfloat)glfwGetTime();
		}


		// Create camera transformations
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 iden;
		glm::mat4 model;
		glm::mat4 wall_transform;
		glm::mat4 explode_transform;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1.0f, 100.0f);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Rotation transform
		rotate_angle = std::min((GLfloat)glfwGetTime() * 1.0f, 15.0f);
		//rotate_angle = 30.0f;
		std::cout << "ELapsed time: " << rotate_angle << std::endl;
		glm::mat4 rotate_transform = glm::mat4();
		rotate_transform = glm::rotate(rotate_transform, rotate_angle, glm::vec3(0.0f, 1.0f, 0.0f));
		
		// Render Big triangle
		glBindVertexArray(VAOs[0]);
		glUniform3f(objectColorLoc, 0.45f, 0.25f, 0.15f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::translate(model, glm::vec3(-0.03f, -0.34, 1.355f));
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);

		// Render Big Triangle 
		glBindVertexArray(VAOs[1]);
		glUniform3f(objectColorLoc, 0.5f, 0.2f, 0.1f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::translate(model, glm::vec3(-0.03f, 0.08f, 2.35f));
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-225.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);
		

		// Render Right Ear Triangle
		glBindVertexArray(VAOs[2]);
		glUniform3f(objectColorLoc, 0.35f, 0.18f, 0.1f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::translate(model, glm::vec3(-1.10f, 0.33f, 0.0f));
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);


		// Render Square
		glBindVertexArray(VAOs[3]);
		glUniform3f(objectColorLoc, 0.35f, 0.25f, 0.2f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::scale(model, glm::vec3(1.15, 1.0, 1.35));
			model = glm::translate(model, glm::vec3(-0.35f, 0.5f, 0.01f));
			
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotates to become straight

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		// Render Left Triangle
		glBindVertexArray(VAOs[4]);
		glUniform3f(objectColorLoc, 0.6f, 0.3f, 0.2f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::translate(model, glm::vec3(1.12f, 1.04f, 0.0f));
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
			model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);

		
		// Render Medium Triangle
		glBindVertexArray(VAOs[5]);
		glUniform3f(objectColorLoc, 0.3f, 0.2f, 0.15f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::translate(model, glm::vec3(-0.03f, -1.755f, 1.35f));
			if (firstPhaseCompleted) {
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(currentTime - animationStartTime) * 0.75));
			}
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);
		
		// Render Parellelogram
		glBindVertexArray(VAOs[6]);
		glUniform3f(objectColorLoc, 0.5f, 0.35f, 0.15f);
		model = glm::mat4();
		model *= rotate_transform;
		if (transitionStarted) {
			model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // Flip in Y axis parallelogram upwards
			model = glm::scale(model, glm::vec3(0.65f, 0.65f, 1.0f)); // Shrink Parallelogram to be smaller width
			model = glm::translate(model, glm::vec3(-0.05f, -0.78f, 2.17f));

			model = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.0f)); // FLip in Z axis

			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			if (animationProgress <= 1.0) {
				model = glm::mix(iden, model, animationProgress);
			}


			if (hasTransformed) {
				glm::mat4 secondTransform = model;
				secondTransform = glm::scale(secondTransform, glm::vec3(-1.0f, 1.0f, 1.0f));
				secondTransform = glm::rotate(secondTransform, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

				// Y, Z, X
				secondTransform = glm::translate(secondTransform, glm::vec3(-1.162f, 0.5625f, 0.0f));

				GLfloat t = (currentTime - flipParallelogramStartTime) / duration;
				if (t > 1.0f) { // Prevent continiously increasing
					t = 1.0f;
					if (!flipParallelogram) {
						flipParallelogram = true;
						//scaleDownStartTime = (GLfloat)glfwGetTime() + delayAnimationTime; // Add a delay to allow time to see the final shape
					}
				}
				if (t <= 1.0f) {
					model = glm::mix(model, secondTransform, t);
				}
			}
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		/*
		// Starts a second animation
		if (firstPhaseCompleted && !secondPhaseCompleted && play_animation) {
			//std::cout << "Second animation has started" << std::endl;
			if (!should_explode) {
				should_explode = true;
				explosionStartTime = currentTime + 3.2f;
			}
		}
		GLfloat elapsedTime = currentTime - explosionStartTime;
		GLfloat explosionFactor = glm::clamp(elapsedTime / explosionDuration, 0.0f, 1.0f);

		wall_transform = glm::mat4();
		wall_transform = glm::rotate(wall_transform, rotate_angle, glm::vec3(0.0f, 1.0f, 0.0f));
		wall_transform = glm::translate(wall_transform, glm::vec3(0.0f, 0.0f, -3.579f));
		wall_transform = glm::rotate(wall_transform, glm::radians(-160.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		wall_transform = glm::scale(wall_transform, glm::vec3(1.5f, 1.5f, 1.5f));
		
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(-1.25f, 1.0f, 1.5f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[0]);
		glUniform3f(objectColorLoc, 0.45f, 0.25f, 0.15f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));

		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);

		// Render Small triangle 
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(-1.5f, 1.0f, -1.5f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[1]);
		glUniform3f(objectColorLoc, 0.5f, 0.2f, 0.1f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);


		//Render Small Triangle
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(-0.5f, 1.0f, 0.5f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[2]);
		glUniform3f(objectColorLoc, 0.35f, 0.18f, 0.1f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);


		glm::mat4 squareTransform = wall_transform;
		squareTransform = glm::translate(wall_transform, glm::vec3(0.0f, -0.5f, 0.0f));

		// Render Square
		if (should_explode) {
			explode_transform = squareTransform;
			glm::vec3 explosionOffset = glm::vec3(1.5f, 1.0f, -1.2f) * explosionFactor;
			explode_transform = glm::translate(squareTransform, explosionOffset);
		}
		glBindVertexArray(VAOs[3]);
		glUniform3f(objectColorLoc, 0.35f, 0.25f, 0.2f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : squareTransform));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// Render Large Triangle
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(-1.86f, 1.0f, -1.541f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[4]);
		glUniform3f(objectColorLoc, 0.6f, 0.3f, 0.2f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);


		// Render Medium Triangle
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(-1.5f, -1.0f, 1.5f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[5]);
		glUniform3f(objectColorLoc, 0.3f, 0.2f, 0.15f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));
		glDrawArrays(GL_TRIANGLES, 0, 24);
		glBindVertexArray(0);

		// Render parallelogram
		if (should_explode) {
			explode_transform = wall_transform;
			glm::vec3 explosionOffset = glm::vec3(1.75f, 1.0f, -1.5f) * explosionFactor;
			explode_transform = glm::translate(wall_transform, explosionOffset);
		}
		glBindVertexArray(VAOs[6]);
		glUniform3f(objectColorLoc, 0.3f, 0.2f, 0.15f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(should_explode ? explode_transform : wall_transform));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		if (should_explode && elapsedTime >= explosionDuration) {
			secondPhaseCompleted = true;
		}*/

		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(7, VAOs);
	glDeleteBuffers(7, VBOs);
	glDeleteBuffers(2, EBOs);

	return 0;
}