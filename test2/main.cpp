#include <iostream>

#include <OBDEngine.h>
#include <ResourceManager/ResourceManager.h>
#include <OBDShaderProgram.h>

#include <GLFW/glfw3.h>

int main() {
    ResourceManager *rm = new ResourceManager();

    // Initialise GLFW
	if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if( window == NULL ){
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

    std::cout << "Using OpenGL version: " <<  glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << std::endl;

    OBDEngine *re = new OBDEngine();

    re -> Init();

	re -> createShaderProgram("defaultProgram", "../media/shaders/vertexShader.glsl", "../media/shaders/fragmentShader.glsl");

	re -> setCurrentShaderProgram("defaultProgram");

    OBDLight *light = re -> createLight(OBDColor(1, 1, 1), 1);

    OBDCamera *camera = re -> createCamera();

	camera -> setCameraPosition(glm::vec3(10, 10, 10));
	
	ResourceIMG *img = (ResourceIMG*)rm -> getResource("../media/testBuilding/wall_kaonov_Base_Color.bmp", true);

	// Objeto 1
	OBDObject *object = re -> createObject("../media/testBuilding/wall.obj");
	object -> getMesh("Wall_Cube.003") -> setTexture(OBDEnums::TextureTypes::TEXTURE_AMBIENT, img);

	// Objeto 2
	OBDObject *object2 = re -> createObject("../media/testBuilding/wall.obj");
	object2 -> getMesh("Wall_Cube.003") -> setTexture(OBDEnums::TextureTypes::TEXTURE_AMBIENT, img);
	object2 -> rotate(1.00, -180.00, -3.00, 0.0);
	object2 -> translate(-7.00, 2.50, 4.50);
	object2 -> scale(0.50,0.50,0.50);

	// Objeto 3
	OBDObject *object3 = re -> createObject("../media/testBuilding/wall.obj");
	object3 -> getMesh("Wall_Cube.003") -> setTexture(OBDEnums::TextureTypes::TEXTURE_AMBIENT, img);
	object3 -> translate(5.00, 0.00, 2.00);
	object3 -> scale(1, 1, 1);
	object3 -> rotate(0.00, 90.00, 0.00, 0.0);

	//bucle
	float i = -10.0;
	float var_i = 0.1;
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
		light -> setPosition(glm::vec3(i, 10.00, i));
		i += var_i;
		if (i > 10.0) var_i = -0.1;
		if (i < -10.0) var_i = 0.1;
		// Engine draw
        re -> draw();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    return 0;
}
