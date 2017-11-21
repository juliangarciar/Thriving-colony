#ifndef SCREEN_H
#define SCREEN_H

#include <irrlicht.h>

using namespace irr;

class Screen {

    public:
        Screen(int width, int height);
        ~Screen();

        IrrlichtDevice* getDevice();
        
    private:
        IrrlichtDevice* device;
};

#endif