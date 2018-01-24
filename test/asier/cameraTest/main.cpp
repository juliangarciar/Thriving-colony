#include <iostream>
#include <irrlicht.h>
#include "BirdsEyeCAM.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, 0);

    if(device == 0){
        return 1;
    }

    IVideoDriver* driver = device -> getVideoDriver();
    ISceneManager* smgr = device -> getSceneManager();
    IGUIEnvironment* guienv = device -> getGUIEnvironment();

    // Creamos un cubo simple
    IMeshSceneNode *cubeNode = smgr -> addCubeSceneNode(10);
    if(cubeNode) {
        cubeNode -> setMaterialFlag(EMF_LIGHTING, true);
        cubeNode -> setPosition(vector3df(0,10,0));
    } 

    // Creamos una camara
    ICameraSceneNode* camera = smgr -> addCameraSceneNode(); //0, vector3df(0,30,-40), vector3df(0,5,0) 
    // LLamamos a la funcion de la camara
    BirdsEyeCAM birdseyecam1;
    //birdseyecam1.Update(camera, device, driver);

    while(device -> run()){
        driver -> beginScene(true, true, SColor(255,100,101,140));
        
        birdseyecam1.Update(camera, device, driver); 
        
        smgr -> drawAll();
        guienv -> drawAll();

        driver -> endScene();
    }
    device -> drop();

    return 0;
}