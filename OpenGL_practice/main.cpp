#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader.h"
#include "TriangleMesh.h"

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

	TriangleMesh rectangle;
	rectangle.setVertices({
		50.0f, 50.0f, 0.0f,
		50.0f, -50.0f, 0.0f,
		-50.0f, -50.0f, 0.0f,
		-50.0f, 50.0f, 0.0f
		});

	rectangle.addTriangle(0, 1, 3);
	rectangle.addTriangle(1, 2, 3);

	rectangle.finalize();


	glm::vec3 pivot_vector(0, 0, 50);
	
	// render loop
	// -----------

	ourShader.use();

	float deg2rad = M_PI / 180.0f;

	glm::mat4 identity(1.0f);
	glm::mat4 model_to_device_matrix(1.0f);
	

	model_to_device_matrix = glm::scale(identity, glm::vec3(1.0f / 200.0f, 1.0f / 200.0f, 1.0f / 200.0f));

	glm::mat4 camera_matrix(1.0f);

	camera_matrix = glm::rotate(identity, glm::radians(20.f), glm::vec3(1.0f, 0.0f, 0.0f));
	camera_matrix = glm::rotate(identity, glm::radians(10.f), glm::vec3(0.0f, 1.0f, 0.0f)) * camera_matrix;

	std::vector<glm::vec3> square_base_vecs = { glm::vec3(50.0f,0.0f,0.0f),
												glm::vec3(0.0f,50.0f,0.0f),
												glm::vec3(0.0f,0.0f,50.0f),
												glm::vec3(-50.0f,0.0f,0.0f),
												glm::vec3(0.0f,-50.0f,0.0f),
												glm::vec3(0.0f,0.0f,-50.0f) };


	float i = 1.0f;
	//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

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

		

		//transform_matrix = glm::translate(transform_matrix, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform_matrix = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		*/
		
		
		
		i++;
		// draw our first triangle
		
		for (const auto& vec : square_base_vecs)
		{
			glm::vec3 x = glm::cross(vec, pivot_vector);

			int scalar_product = glm::dot(pivot_vector, vec);

			/// animate
		//scale
			float scale_value = 0.5f;
			i = static_cast<int>(i) % 360;
			glm::vec3 vec(std::cos(glm::radians(i)), std::sin(glm::radians(i)), 0.0f);


			glm::mat4 anim_matrix =
				  glm::scale(identity, glm::vec3(scale_value, scale_value, scale_value))
				* glm::translate(identity, 100.f*vec)
				* glm::rotate(identity, glm::radians(-i), glm::vec3(0.0, 0.0, 1.0));


	
			glm::mat4 transform_matrix;

			glm::mat4 model_cam = model_to_device_matrix * camera_matrix * anim_matrix;

			switch (scalar_product)
			{
				case 0: transform_matrix = model_cam * glm::rotate(identity, glm::radians(90.0f), x)*glm::translate(identity, pivot_vector); break;
				default:
				{
					if (scalar_product < 0)
					{
						transform_matrix = model_cam * glm::rotate(identity, glm::radians(180.0f), glm::vec3(1,0,0))*glm::translate(identity, pivot_vector); break;
					}
					else
					{
						transform_matrix = model_cam * glm::translate(identity, pivot_vector); break;
					}
				}
			}
			

			transform_matrix = transform_matrix * glm::translate(identity, vec);

			ourShader.setMatrix4("transform", transform_matrix);

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			rectangle.render();
		}
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		Sleep(10);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------


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