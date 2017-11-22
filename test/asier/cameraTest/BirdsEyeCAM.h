#pragma once

#include <irrlicht.h>
#include <iostream>

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui;
using namespace std;

class BirdsEyeCAM {

    public:
        BirdsEyeCAM();
        ~BirdsEyeCAM();
        void Update(ICameraSceneNode *,IrrlichtDevice *,IVideoDriver *);

};