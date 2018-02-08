#include <iostream>
#include <queue>
#include <irrlicht.h>
#include "nodeGrid.h"
#include "grid.h"
#include "aStar.h"
#include "troop.h"
#include "MyEventReceiver.h"
#include <time.h>
using namespace std;
using namespace irr;

//MAIN FUNCTION
i32 main(){
    i32 gridX = 24;
    i32 gridY = 24;

    //INIT START AND END
    i32 pStartX;
    i32 pStartY;
    i32 pEndX;
    i32 pEndY;
    std::cout << "Introduzca las coordenadas de un waypoint de inicio (0 a 19)." << endl;
    std::cout << "X: ";
    std::cin >> pStartX;
    std::cout << "Y: ";
    std::cin >> pStartY;
    std::cout << "Introduzca las coordenadas de un waypoint de destino (0 a 19)." << endl;
    std::cout << "X: ";
    std::cin >> pEndX;
    std::cout << "Y: ";
    std::cin >> pEndY;

    //IRRLICHT
    irr::SIrrlichtCreationParameters params;

    params.DriverType = video::EDT_OPENGL;
    params.WindowSize = core::dimension2d<u32>(640, 480);
    IrrlichtDevice *device = createDeviceEx(params);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver *driver = device -> getVideoDriver();
    scene::ISceneManager *smgr = device -> getSceneManager();
    driver -> setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    //INIT MAP DATA
    grid* mapita = new grid(gridX, gridY, smgr);
    
    
    nodeGrid *start = mapita -> getGrid()[pStartX][pStartY];
    nodeGrid *end = mapita -> getGrid()[pEndX][pEndY];
    start -> setCameFrom(NULL);
    start -> setCounted(true);
    start -> setWeight(0);

        start -> swapColor(irr::video::SColor(0, 0, 0, 255));
        end -> swapColor(irr::video::SColor(0, 255, 0, 0));

        
        //DRAW OBSTACLES
        for (i32 x = 13, y = 15; x < 20; x++, y--)
        {
            if(start -> getX() != x && end -> getX() != x && start -> getY() != y && end -> getY() != y){
                mapita -> getGrid()[x][y] -> swapColor(irr::video::SColor(0, 0, 0, 0));
                mapita -> getGrid()[x][y] -> setBlock(true);
            }
            
        }
        for (i32 x = 12, y = 15; x < 20; x++, y--)
        {
            if (start -> getX() != x && end -> getX() != x && start -> getY() != y && end -> getY() != y)
            {
                mapita -> getGrid()[x][y] -> swapColor(irr::video::SColor(0, 0, 0, 0));
                mapita -> getGrid()[x][y] -> setBlock(true);
            }
            
        }
        aStar *estrella = new aStar(mapita, start, end);
       

        //ADD IRRLICHT CAMERA
        scene::ICameraSceneNode *camera =
            smgr -> addCameraSceneNodeFPS();

        camera -> setPosition(core::vector3df(0, 500, 20));
        camera -> setTarget(core::vector3df(0, 0, 0));
        camera -> setFarValue(2000.0f);
        //MORE THINGS
        //bool done = false;
        std::vector<nodeGrid *> pathFind;
        //irr::core::vector3df *movData = new irr::core::vector3df(0, 0, 20.f);
        irr::core::vector3df movData;
        //troop *selectedTroop = NULL;
        troop *character = NULL;
        character = new troop(0, 0, 1, smgr);
        MyEventReceiver event;
        device -> setEventReceiver(&event);
        //NUEVO VERSION
        irr::scene::ISceneManager *sceneManager;
        sceneManager = device -> getSceneManager();
        irr::scene::ISceneCollisionManager *collisionManager;
        collisionManager = sceneManager -> getSceneCollisionManager();
        irr::core::triangle3df triangle;
        //irr::scene::ISceneNode *node = 0;
        //clock_t gameTime;
        //NUEVO TERRENO
        scene::ITerrainSceneNode *currentTerrain =
            sceneManager -> addTerrainSceneNode(

                "media/heightmap.bmp",            // height map
                0,                                // parent node
                -1,                               // node id
                core::vector3df(0.f, -60.f, 0.f), // position

                core::vector3df(0.f, 0.f, 0.f),     // rotation
                core::vector3df(100.f, 1.f, 100.f), // scale

                video::SColor(125, 125, 125, 125), // vertexColor

                5,              // maxLOD
                scene::ETPS_17, // patchSize
                4);
        irr::scene::ITriangleSelector *selector = sceneManager -> createTerrainTriangleSelector(currentTerrain);

        currentTerrain -> setTriangleSelector(selector);

        //MAIN BUCLE
        while (device -> run())
        {
            if (device -> isWindowActive())
            {

                driver -> beginScene(true, true, 0);

                if (event.GetMouseState().RightButtonDown)
                {

                    //irr::gui::ICursorControl *myCursor = device -> getCursorControl();
                    //irr::core::vector2di pos = myCursor -> getPosition();
                    //
                    //irr::core::line3df ray = collisionManager -> getRayFromScreenCoordinates(pos);
                    ////std::cout << "X :" << pos.X << "Y :" << pos.Y << endl;
                    //
                    //if (collisionManager -> getCollisionPoint(ray, selector, movData, triangle, node))
                    //{
                    //    if(!done){
                    //        cout << "OMG" << endl;
                    //        cout << "X: " << movData.X << " Y: " << movData.Z << endl;
                    //
                    //        character -> setDes(movData);
                    //        done = true;
                    //    }
                    //    else{
                    //        done = false;
                    //    }
                    //}
                    estrella -> startAlgoritm();
                }

                //Character update
                //character -> updateTroop();
                //Draw scene
                smgr -> drawAll();
                driver -> endScene();
            }
    }
    delete start;
    delete end;
    delete mapita;
    delete estrella;
    return 0;
}