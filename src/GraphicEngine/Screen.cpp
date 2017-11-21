#include "Screen.h"

using namespace irr;

Screen::Screen(int width, int height) {
    irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(640, 480);
    device = createDeviceEx(params);
    
    if (device == 0) exit(0); 

	// disable mouse cursor
	device->getCursorControl()->setVisible(true);
}

Screen::~Screen() {
    delete device;
    device = NULL;
}

IrrlichtDevice* Screen::getDevice() {
    return device;
}