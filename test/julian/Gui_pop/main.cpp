#include <iostream>
#include <queue>
#include <irrlicht.h>
#include "nodeGrid.h"
#include "grid.h"
#include "aStar.h"
using namespace std;
using namespace irr;

//MAIN FUNCTION
int main(){
    bool done = false;
    //IRRLICHT
    irr::SIrrlichtCreationParameters params;

    params.DriverType = video::EDT_OPENGL;
    params.WindowSize = core::dimension2d<u32>(640, 480);
    IrrlichtDevice *device = createDeviceEx(params);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver *driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    
    //ADD IRRLICHT CAMERA
    scene::ICameraSceneNode *camera =
        smgr->addCameraSceneNodeFPS();

        camera->setPosition(core::vector3df(0, 500, 20));
        camera->setTarget(core::vector3df(0, 0, 0));
        camera->setFarValue(2000.0f);

    //INIT MAP DATA
    grid* mapita = new grid(25, 25, smgr);
    
    //INIT START AND END
    nodeGrid *start = mapita->getGrid()[4][5];
    nodeGrid *end = mapita->getGrid()[18][13];
    
    start->setCameFrom(NULL);
    start->setWeight(0);

        start->swapColor(irr::video::SColor(0, 0, 0, 255));
        end->swapColor(irr::video::SColor(0, 255, 0, 0));

    
        //DRAW OBSTACLES
        for (int x = 13, y = 15; x < 20; x++, y--)
        {
            mapita->getGrid()[x][y]->swapColor(irr::video::SColor(0, 0, 0, 0));
            mapita->getGrid()[x][y]->setBlock(true);
        }
    aStar* estrella = new aStar(mapita, start, end);
    //MAIN BUCLE
    while (device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, 0);

                if(!done){
                    estrella->startAlgoritm();
                }

            //Draw scene
            smgr->drawAll();
            driver->endScene();
        }
    }
    delete start;
    delete end;
    delete mapita;

    return 0;
}