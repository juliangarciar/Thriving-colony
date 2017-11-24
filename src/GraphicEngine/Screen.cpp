#include "Screen.h"

using namespace irr;

Screen* Screen::pinstance = 0;

Screen* Screen::Instance(){
    
    if(pinstance == 0){
        pinstance = new Screen(1280, 720);
    }
    
    return pinstance;
}

Screen::Screen(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    io = new InputManager();

    irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(width, height);
    params.EventReceiver=io;
    device = createDeviceEx(params);
    
    if (device == 0) exit(0); 

	// disable mouse cursor
	device->getCursorControl()->setVisible(true);

	driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	scene = device->getSceneManager();
	gui = device->getGUIEnvironment();

    dtThen = device->getTimer()->getTime();
}

Screen::~Screen() {
    delete device;
    device = NULL;
}

void Screen::beginScene(){
    float now = device->getTimer()->getTime();
    deltaTime = (float)(now - dtThen) / 1000.f; // Time in seconds
    dtThen = now;

    driver->beginScene(true, true, 0 );
}

void Screen::endScene(){
    scene->drawAll();
    gui->drawAll();

    driver->endScene();
}

bool Screen::isOpen(){
    return device->run();
}

bool Screen::isReady(){
    return device->isWindowActive();
}

void Screen::close(){
    device->drop();
}

IrrlichtDevice* Screen::getDevice() {
    return device;
}

video::IVideoDriver* Screen::getVideoDriver(){
    return driver;
}

scene::ISceneManager* Screen::getSceneManager(){
    return scene;
}

gui::IGUIEnvironment* Screen::getGUIEnvironment(){
    return gui;
}

int Screen::getScreenWidth(){
    return screenWidth;
}

int Screen::getScreenHeight(){
    return screenHeight;
}

float Screen::getDeltaTime(){
    return deltaTime;
}

InputManager *Screen::getIO(){
    return io;
}