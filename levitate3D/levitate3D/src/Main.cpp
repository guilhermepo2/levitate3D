#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

const char* vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 aColor;\nout vec3 ourColor;\nvoid main()\n{\ngl_Position = vec4(aPos, 1.0);\nourColor = aColor;\n}\0";

const char* fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nin vec3 ourColor;\nvoid main()\n{\nFragColor = vec4(ourColor, 1.0f);\n}\0";

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void) {

	glfwInit();

	// the first argument of glfwWindowHint tells us what option we want to configure
	//	the second argument sets the value of the option
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*	
		GLFWwindow* glfwCreateWindow (	
		int 			width,
		int 			height,
		const char* 	title,
		GLFWmonitor* 	monitor,
		GLFWwindow*  	share 
		)
	*/
	GLFWwindow* window = glfwCreateWindow(1024, 576, "GLFW Window", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// telling opengl the size of the rendering window (?!)
	glViewport(0, 0, 1024, 576);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	while (!glfwWindowShouldClose(window)) {
		// Processing Input
		ProcessInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Shader OurShader("./src/assets/vertex.glsl", "./src/assets/fragment.glsl");

		float vertices[] = {
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		// vertex array object
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// vertex buffer object -> sends data to the vertex shader
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copies data to the buffer

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// draw the triangle!
		OurShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Calling events and swaping buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}