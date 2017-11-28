#include "Input.h"
#include <irrlicht.h>

using namespace irr;
using namespace std;

Input::Input(){

}

Input::~Input() {

}

bool Input::OnEvent(const SEvent& event) {

    if (event.EventType == EET_GUI_EVENT) {

        s32 id = event.GUIEvent.Caller->getID();
        gui::IGUIEnvironment* env = device->getGUIEnvironment();

        switch(event.GUIEvent.EventType) {
        
        // Input del mouse al hacer click
        case gui::EGET_BUTTON_CLICKED:
            switch(id) {

            case GUI_ID_QUIT_BUTTON:
                device->closeDevice();
                return true;

            case GUI_ID_NEW_WINDOW_BUTTON: {

                //Context.listbox->addItem(L"Window created");
                counter += 200;
                if (counter > 5000)
                    counter = 0;
                
                // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
                // tambien se cree una caja en las coordenadas actuales del cursor del raton.
                //scene::ISceneManager* smgr2 = Context.device->getSceneManager();
                
                
                //scene::IMesh* cube = smgr2->getGeometryCreator()->createCubeMesh();
                scene::IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(100);

                if(cubeNode) {
                    cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
                    cubeNode->setPosition(core::vector3df(500 + Context.counter,500,2500));
                }

            }
                return true;

            default:
                return false;
            }
            break;

        default:
            break;
        }
    }
    return false;
}

void Terrain(IrrlichtDevice * device, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * env, ICameraSceneNode * camera, ITerrainSceneNode * terrain, ITriangleSelector * slector, ICursorControl * cursor, ISceneCollisionManager * collisionManager, ISceneNode * sphere) {
    device = device;
    driver = driver;
    smgr = smgr;
    env = env;
    camera = camera;
    terrain = terrain;
    selector = selector;
    cursor = cursor;
    collisionManager = collisionManager;
    sphere = sphere;

    device->setWindowCaption(L"Irrlicht Engine - Interface");
    device->setResizable(true);
    
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    // Camera
    camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
	camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
    camera->setFarValue(42000.0f);
    
    // Terrain
    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, driver->getTexture("terrain-texture.jpg"));
	terrain->setMaterialTexture(1, driver->getTexture("detailmap3.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
    
    // Add the buttons
	env->addButton(core::rect<s32>(core::position2d<s32>(540, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_QUIT_BUTTON,
			L"Quit", L"Exits Program");
	env->addButton(core::rect<s32>(core::position2d<s32>(540, 350), core::dimension2d<s32>(200, 60)), 0, GUI_ID_NEW_WINDOW_BUTTON,
			L"New Window", L"Launches a new Window");
	env->addButton(core::rect<s32>(core::position2d<s32>(1040, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_FILE_OPEN_BUTTON,
            L"File Open", L"Opens a file");
            
}
