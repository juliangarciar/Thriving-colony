#include "Window.h"
using namespace irr;

Window* Window::pinstance = 0;

Window* Window::Instance() {
    
    if(pinstance == 0) {
        pinstance = new Window();
    }
    
    return pinstance;
}

Window::Window() {
    closeWindow = false;
    
    glfwInit();

    // Init last delta time
    lastDeltaTime = 0.014;
}

Window::~Window() {
    //ToDo: destructor
}

void Window::Init(i32 width, i32 height){
    windowWidth = width;
    windowHeight = height;
    screenCenter = Vector2<i32>(windowWidth/2, windowHeight/2);

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

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, i32 width, i32 height) {
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
			Window::Instance() -> windowWidth = width;
			Window::Instance() -> windowHeight = height;
    		Window::Instance() -> screenCenter.set(width/2, height/2);
			Window::Instance() -> triggerResizeCallback(width, height);
        }
    );

    dtThen = glfwGetTime();
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
    if (b) scene -> drawAll();
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

void Window::setResizeCallback(std::function<void(i32, i32)> f){
	resizeCallback = f;
}

void Window::triggerResizeCallback(i32 width, i32 height){
	if (resizeCallback) resizeCallback(width, height);
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

i32 Window::getWindowWidth(){
    return windowWidth;
}

i32 Window::getWindowHeight(){
    return windowHeight;
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
    framerate = floor(1.0 / getDeltaTime());
}

i32 Window::getFrameRate() {
    return framerate;
}