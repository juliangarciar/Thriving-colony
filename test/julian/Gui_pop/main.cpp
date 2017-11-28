#include <iostream>
#include <queue>
#include <irrlicht.h>
#include "nodeGrid.h"
#include "grid.h"
#include "aStar.h"
#include <time.h>
using namespace std;
using namespace irr;

//MAIN FUNCTION
int main(){
    int gridX = 24;
    int gridY = 24;
    int camino = 0;
    bool done = false;
    int mepiro=2;
    int mepiroX = 0;
    int mepiroY = 0;
    std::vector< nodeGrid* > pathFind;
    nodeGrid* character;
    //clock_t t;
    int t = 0;
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
    grid* mapita = new grid(gridX, gridY, smgr);
    
    //INIT START AND END
    nodeGrid *start = mapita->getGrid()[0][0];
    nodeGrid *end = mapita->getGrid()[20][20];
    character = new nodeGrid(0, 0, 1, smgr);

    character->swapColor(irr::video::SColor(0, 125, 125, 125));
    start->setCameFrom(NULL);
    start->setCounted(true);
    start->setWeight(0);

        start->swapColor(irr::video::SColor(0, 0, 0, 255));
        end->swapColor(irr::video::SColor(0, 255, 0, 0));


        //DRAW OBSTACLES
        for (int x = 13, y = 15; x < 20; x++, y--)
        {
            mapita->getGrid()[x][y]->swapColor(irr::video::SColor(0, 0, 0, 0));
            mapita->getGrid()[x][y]->setBlock(true);
        }
        for (int x = 12, y = 15; x < 20; x++, y--)
        {
            mapita->getGrid()[x][y]->swapColor(irr::video::SColor(0, 0, 0, 0));
            mapita->getGrid()[x][y]->setBlock(true);
        }
        aStar *estrella = new aStar(mapita, start, end);
        //MAIN BUCLE
        while (device->run())
        {
            if (device->isWindowActive())
            {
                driver->beginScene(true, true, 0);

                if (!done)
                {
                    pathFind = estrella->startAlgoritm();
                    camino = 0;
                    cout << camino << endl;
                    done = true;
                    //t = clock();
                }
                if (t > 50)
                {
                    mepiroX = pathFind.at(camino)->getX();
                    mepiroY = pathFind.at(camino)->getY();
                    character->getCube()->setPosition(irr::core::vector3df(0, mepiro * 1.f, 0));
                    //camino++;
                    //camino < pathFind.size()
                    mepiro++;
                    t = 0;
                    //t = clock();
                }
                t++;
                //Draw scene
                smgr->drawAll();
                driver->endScene();
            }
    }
    delete start;
    delete end;
    delete mapita;
    delete estrella;
    return 0;
}