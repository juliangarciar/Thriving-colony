#include "Window.h"

Window* Window::pinstance = 0;

Window* Window::Instance() {
    if(pinstance == 0) {
        pinstance = new Window(1048, 720);
    }
    return pinstance;
}

Window::Window(i32 width, i32 height) {
    closeWindow = false;
    windowWidth = width;
    windowHeight = height;

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
    window = glfwCreateWindow(windowWidth, windowHeight, "Thriving Colony", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    std::cout << "Using OpenGL version: " <<  glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << std::endl;

    glfwMakeContextCurrent(window);

    e = new OBDEngine();
	e -> Init(windowWidth, windowHeight);
	e -> createShaderProgram("defaultProgram", "media/shaders/vertexShader.glsl", "media/shaders/fragmentShader.glsl");
	e -> setCurrentShaderProgram("defaultProgram");
   
    // create gui manager    
    gui = new nanogui::Screen();
    gui -> initialize(window, true);

    glfwSetWindowUserPointer(window, gui);

    glfwSetCharCallback(window,
        [](GLFWwindow *w, u32 codepoint) {
            Window::Instance() -> getGUIEnvironment() -> charCallbackEvent(codepoint);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, i32 width, i32 height) {
			Window::Instance() -> getEngine() -> setWindowSize(width, height);
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
        }
    );

    dtThen = glfwGetTime();

    billboardLayer = e -> createShaderedSceneNode("media/shaders/vertexShader.glsl", "media/shaders/fragmentShaderBillboards.glsl");
}

Window::~Window() {
    //ToDo: destructor
}

void Window::setGUI(){ 
    gui -> setVisible(true);
    gui -> performLayout();
}

void Window::beginScene(){
    f64 now = glfwGetTime();
    deltaTime = (f64)(now - dtThen); // Time in seconds
    dtThen = now;
}

void Window::endScene(){
	e->draw();
    gui -> drawWidgets();
    glEnable(GL_DEPTH_TEST);
	glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::close(){
    closeWindow = true;
}

bool Window::isOpen(){
    return (!glfwWindowShouldClose(window) && !closeWindow);
}

void Window::onClose(){
    glfwTerminate();
}

OBDEngine *Window::getEngine(){
	return e;
}

nanogui::Screen* Window::getGUIEnvironment(){
    return gui;
}

i32 Window::getInitialWindowWidth(){
    return windowWidth;
}

i32 Window::getInitialWindowHeight(){
    return windowHeight;
}

i32 Window::getRealWindowWidth(){
    return windowWidth;
}

i32 Window::getRealWindowHeight(){
    return windowHeight;
}

f32 Window::getDeltaTime() {
    return deltaTime;
}

void Window::calculateFramerate() {
    framerate = floor(1.0 / deltaTime);
}

i32 Window::getFrameRate() {
    return framerate;
}

OBDSceneNode* Window::getBillboardLayer() {
    return billboardLayer;
}