#include "Screen.h"

using namespace irr;

Screen* Screen::pinstance = 0;

Screen* Screen::Instance(){
    
    if(pinstance == 0){
        pinstance = new Screen(640, 480);
    }
    
    return pinstance;
}

Screen::Screen(int width, int height) {
    irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(640, 480);
    device = createDeviceEx(params);
    
    if (device == 0) exit(0); 

	// disable mouse cursor
	device->getCursorControl()->setVisible(true);

	driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	scene = device->getSceneManager();
	gui = device->getGUIEnvironment();
}

Screen::~Screen() {
    delete device;
    device = NULL;
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