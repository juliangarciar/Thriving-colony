#include "Window.h"
using namespace irr;

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

    irr::SIrrlichtCreationParameters params;
    params.DeviceType = E_DEVICE_TYPE::EIDT_GLFW3;
    params.DriverType = video::E_DRIVER_TYPE::EDT_OPENGL;
    params.WindowId = window;
    params.IgnoreInput = true;
    params.WindowSize = core::dimension2du(windowWidth, windowHeight);
    device = createDeviceEx(params);
    if (!device) {
        std::cout << "Failed to initialize Irrlicht" << std::endl;
        exit(0); 
    }

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
        [](GLFWwindow *w, u32 codepoint) {
            Window::Instance() -> getGUIEnvironment() -> charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *w, i32 count, const char **filenames) {
            //Window::Instance() -> getGUIEnvironment() -> dropCallbackEvent(count, filenames);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, i32 width, i32 height) {
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
        }
    );

    dtThen = glfwGetTime();
    // Init last delta time
    lastDeltaTime = 0.014;
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
    lastDeltaTime = deltaTime;
    deltaTime = (double)(now - dtThen); // Time in seconds
    dtThen = now;
    

    driver -> beginScene(true, true, video::SColor(0,0,0,0));
}

void Window::endScene(bool b){
<<<<<<< HEAD
    //std::cout << "Window::endScene init" << std::endl;
    //std::cout << "1" << std::endl;
    // DA ERROR AQUI
    if (b) scene -> drawAll();
    //std::cout << "2" << std::endl;
    gui -> drawWidgets();
    //std::cout << "3" << std::endl;
    glEnable(GL_DEPTH_TEST);
    //std::cout << "4" << std::endl;
    driver -> endScene();
    //std::cout << "Window::endScene finish" << std::endl;
=======
    // DA ERROR AQUI
    if (b) scene -> drawAll();
    gui -> drawWidgets();
    glEnable(GL_DEPTH_TEST);
    driver -> endScene();
>>>>>>> master
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

i32 Window::getInitialWindowWidth(){
    return windowWidth;
}

i32 Window::getInitialWindowHeight(){
    return windowHeight;
}

i32 Window::getRealWindowWidth(){
    return windowWidth;
    //return driver -> getViewPort().getWidth(); 
}

i32 Window::getRealWindowHeight(){
    return windowHeight;
    //return driver -> getViewPort().getHeight(); 
}

f32 Window::getDeltaTime() const{
    return deltaTime;
}

f32 Window::getLastDeltaTime() const{
    return lastDeltaTime;
}

f32 Window::getDeltaTimeVariance() const{
    return deltaTime / 0.016f;
}

void Window::calculateFramerate() {
    framerate = floor(1.0 / Window::Instance() -> getDeltaTime());
}

i32 Window::getFrameRate() {
    return framerate;
}