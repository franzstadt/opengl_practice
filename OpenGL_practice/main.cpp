#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#include <iostream>
#include <vector>


//#include <stdio.h>
//#include <cstdio>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Shader ourShader("vertex.shader", "fragment.shader");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	/*float vertices[] = 
	{
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	*/

	float rectangle_vertices[] =
	{
		100.0f, 100.0f, 0.0f,
		100.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 100.0f, 0.0f
	};


	unsigned int indices[] = 
	{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
	*/

	// render loop
	// -----------

	ourShader.use();

	float deg2rad = M_PI / 180.0f;

	glm::mat4 identity(1.0f);
	glm::mat4 transform_matrix(1.0f);
	glm::mat4 model_to_device_matrix(1.0f);
	

	model_to_device_matrix = glm::scale(identity, glm::vec3(1.0f / 200.0f, 1.0f / 200.0f, 1.0f / 200.0f));

	glm::mat4 camera_matrix(1.0f);

	camera_matrix = glm::rotate(identity, glm::radians(20.f), glm::vec3(1.0f, 0.0f, 0.0f));
	camera_matrix = glm::rotate(identity, glm::radians(60.f), glm::vec3(0.0f, 1.0f, 0.0f)) * camera_matrix;

	std::vector<glm::vec3> square_base_vecs = { glm::vec3(50.0f,0.0f,0.0f),
												glm::vec3(0.0f,50.0f,0.0f),
												glm::vec3(0.0f,0.0f,50.0f),
												glm::vec3(-50.0f,0.0f,0.0f),
												glm::vec3(0.0f,-50.0f,0.0f),
												glm::vec3(0.0f,0.0f,-50.0f) };


	float i = 1.0f;
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//transform_matrix = identity;

		

		

		//transform_matrix = glm::rotate(transform_matrix, glm::radians(20), glm::vec3(1.0, 0.0, 0.0));

		/*
		//scale
		float scale_value = 0.5f;
		transform_matrix = glm::scale(transform_matrix, glm::vec3(scale_value, scale_value, scale_value));

		//rotate
		transform_matrix = glm::rotate(transform_matrix, glm::radians(i), glm::vec3(0.0, 0.0, 1.0));

		//shift
		i = static_cast<int>(i) % 360;
		glm::vec3 vec(std::cos(glm::radians(i)), std::sin(glm::radians(i)), 0.0f);
		transform_matrix = glm::translate(transform_matrix, vec);

		//transform_matrix = glm::translate(transform_matrix, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform_matrix = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		*/
		
		
		
		i++;
		// draw our first triangle
		
		for (const auto& vec : square_base_vecs)
		{
			transform_matrix = model_to_device_matrix * camera_matrix;

			transform_matrix = transform_matrix * glm::translate(identity, vec);

			unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		// glBindVertexArray(0); // no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		Sleep(10);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}