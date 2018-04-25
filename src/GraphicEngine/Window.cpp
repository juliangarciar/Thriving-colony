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
    
    glfwInit();
    glfwSetTime(0);

    // Create an application window with the following settings:
    window = glfwCreateWindow(windowWidth, windowHeight, "Thriving Colony", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);

    e = new OBDEngine();
	e -> Init(windowWidth, windowHeight);
   
    // create gui manager    
    gui = new nanogui::Screen();
    gui -> initialize(window, true);

    glfwSetWindowUserPointer(window, gui);

    glfwSetCharCallback(window,
        [](GLFWwindow *w, u32 codepoint) {
            Window::Instance() -> getGUIEnvironment() -> charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *w, i32 count, const char **filenames) {
            Window::Instance() -> getGUIEnvironment() -> dropCallbackEvent(count, filenames);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, i32 width, i32 height) {
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
        }
    );

    dtThen = glfwGetTime();
}

Window::~Window() {
    //ToDo: destructor
}

void Window::setGUI(){ 
    gui -> setVisible(true);
    gui -> performLayout();
}

void Window::beginScene(){
    double now = glfwGetTime();
    deltaTime = (double)(now - dtThen); // Time in seconds
    dtThen = now;
}

void Window::endScene(){
	e->draw();
    gui -> drawWidgets();
    glEnable(GL_DEPTH_TEST);
	glfwSwapBuffers(window);
}

void Window::close(){
    closeWindow = true;
}

bool Window::isOpen(){
    glfwPollEvents();
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