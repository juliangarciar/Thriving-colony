#include <GLFW/glfw3.h>
#include <OBDEngine/OBDEngine.h>

i32 main() {
    if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(0);
	}
	
	glfwSetTime(0);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create an application window with the following settings:
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Thriving Colony", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);

    OBDEngine *e = new OBDEngine();
	e -> Init(1280, 720);
	e -> createShaderProgram("defaultProgram", "../media/shaders/vertexShader.glsl", "../media/shaders/fragmentShader.glsl");
	e -> setCurrentShaderProgram("defaultProgram");

	OBDCamera *camera = e->createCamera(10000, 45);
	camera->setTargetPosition(glm::vec3(0, 0, 0));
	camera->setCameraPosition(glm::vec3(500, 500, 500));

	OBDLight *light = e->createLight(OBDColor(1, 1, 1, 1), 1, 1, 10);

    while (!glfwWindowShouldClose(window)){

		e->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glfwTerminate();

	return 0;
}