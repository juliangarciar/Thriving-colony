#include "Window.h"
using namespace irr;

Window* Window::pinstance = 0;

Window* Window::Instance() {
    
    if(pinstance == 0) {
        pinstance = new Window(1280, 720);
    }
    
    return pinstance;
}

Window::Window(int width, int height) {
    closeWindow = false;

    windowWidth = width;
    windowHeight = height;

    glfwInit();
    glfwSetTime(0);

    nanogui::init();

    // Create an application window with the following settings:
    window = glfwCreateWindow(windowWidth, windowHeight, "Thriving Colony", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);

    irr::SIrrlichtCreationParameters params;
    params.DeviceType = E_DEVICE_TYPE::EIDT_GLFW3;
    params.DriverType = video::E_DRIVER_TYPE::EDT_OPENGL;
    params.WindowId = window;
    params.IgnoreInput = true;
    params.WindowSize = core::dimension2du(windowWidth, windowHeight);
    device = createDeviceEx(params);
    if (!device) exit(0); 

    // create video driver
	driver = device -> getVideoDriver();
    driver -> setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    // create scene manager
	scene = device -> getSceneManager();

    // create gui manager    
    gui = new nanogui::Screen();
    gui -> initialize(window, true);

    glfwSetWindowUserPointer(window, gui);

    glfwSetCharCallback(window,
        [](GLFWwindow *w, unsigned int codepoint) {
            Window::Instance() -> getGUIEnvironment() -> charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *w, int count, const char **filenames) {
            Window::Instance() -> getGUIEnvironment() -> dropCallbackEvent(count, filenames);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, int width, int height) {
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
        }
    );

    dtThen = glfwGetTime();
}

Window::~Window() {
    //ToDo: borrar device
    //device = NULL; 
}

void Window::setGUI(){ 
    gui -> setVisible(true);
    gui -> performLayout();
}
 
void Window::beginScene(){
    double now = glfwGetTime();
    deltaTime = (double)(now - dtThen); // Time in seconds
    dtThen = now;

    driver -> beginScene(true, true, video::SColor(0,0,0,0));
}

void Window::endScene(){
    scene -> drawAll();
    gui -> drawWidgets();
    glEnable(GL_DEPTH_TEST);

    driver -> endScene();
}

void Window::close(){
    closeWindow = true;
}

bool Window::isOpen(){
    glfwPollEvents();
    return (!glfwWindowShouldClose(window) && !closeWindow);
}

void Window::onClose(){
    device -> drop();
    glfwTerminate();
}

IrrlichtDevice* Window::getDevice() {
    return device;
}

video::IVideoDriver* Window::getVideoDriver() {
    return driver;
}

scene::ISceneManager* Window::getSceneManager() {
    return scene;
}

nanogui::Screen* Window::getGUIEnvironment(){
    return gui;
}

int Window::getInitialWindowWidth(){
    return windowWidth;
}

int Window::getInitialWindowHeight(){
    return windowHeight;
}

int Window::getRealWindowWidth(){
    return windowWidth;
    //return driver -> getViewPort().getWidth(); 
}

int Window::getRealWindowHeight(){
    return windowHeight;
    //return driver -> getViewPort().getHeight(); 
}

float Window::getDeltaTime() {
    return deltaTime;
}