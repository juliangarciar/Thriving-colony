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
    screenWidth = width;
    screenHeight = height;

    irr::SIrrlichtCreationParameters params;
	params.DriverType = video::EDT_OPENGL;
	params.WindowSize = core::dimension2d<u32>(width, height);
    device = createDeviceEx(params);
    
    if (device == 0) exit(0); 

	// enable mouse cursor
	device -> getCursorControl() -> setVisible(true);

	driver = device -> getVideoDriver();
    driver -> setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	scene = device -> getSceneManager();
	gui = device -> getGUIEnvironment();

    for (s32 i=0; i<irr::gui::EGDC_COUNT; ++i) {
        video::SColor col = gui -> getSkin() -> getColor((gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(225);
        gui -> getSkin() -> setColor((gui::EGUI_DEFAULT_COLOR)i, col);
    }

    dtThen = device -> getTimer() -> getTime();
}

Window::~Window() {
    //ToDo: borrar device
    //device = NULL; 
}

void Window::setEventReceiver(IEventReceiver *receiver) {
    device -> setEventReceiver(receiver);
}
 
void Window::beginScene() {
    float now = device -> getTimer() -> getTime();
    deltaTime = (float)(now - dtThen) / 1000.f; // Time in seconds
    dtThen = now;

    driver -> beginScene(true, true, 0 );
}

void Window::endScene() {
    scene -> drawAll();
    gui -> drawAll();

    driver -> endScene();
}

bool Window::isOpen() {
    return device -> run();
}

bool Window::isReady() {
    return device -> isWindowActive();
}

void Window::close() {
    device -> drop();
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

gui::IGUIEnvironment* Window::getGUIEnvironment() {
    return gui;
}

int Window::getInitialWindowWidth() {
    return screenWidth;
}

int Window::getInitialWindowHeight() {
    return screenHeight;
}

int Window::getRealWindowWidth() {
    return driver -> getViewPort().getWidth(); 
}

int Window::getRealWindowHeight() {
    return driver -> getViewPort().getHeight(); 
}

float Window::getDeltaTime() {
    return deltaTime;
}