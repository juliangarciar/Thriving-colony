/*#ifndef INPUT_H
#define INPUT_H*/

#include <irrlicht.h>
#include "../../../src/GraphicEngine/Vector2.h"
#include "../../../src/GraphicEngine/Vector3.h"
#include "../../../src/GraphicEngine/Terrain.h"

using namespace irr;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
/*struct SAppContext {
	IrrlichtDevice *device;
	s32				counter; 
};*/

enum {
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
};

class Input : public IEventReceiver {
    public:
        Input();
        ~Input();

        bool OnEvent(const SEvent& event);
        void Terrain(IrrlichtDevice *, video::IVideoDriver *, scene::ISceneManager *, gui::IGUIEnvironment *, scene::ICameraSceneNode *, scene::ITerrainSceneNode *, scene::ITriangleSelector *, gui::ICursorControl *, scene::ISceneCollisionManager *, scene::ISceneNode *);
    
    private:
        //SAppContext & Context;
        int counter = 0;

        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::ISceneManager* smgr;
        gui::IGUIEnvironment* env;
        scene::ICameraSceneNode* camera;
        scene::ITerrainSceneNode* terrain;
        scene::ITriangleSelector* selector;
        gui::ICursorControl* cursor;
        scene::ISceneCollisionManager* collisionManager;
        scene::ISceneNode* sphere;

        Vector3<float> xyzPointCollision; // xyz del terreno
        int x, y, z;
};
