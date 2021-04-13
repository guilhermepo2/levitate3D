#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

		// Calling events and swaping buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}