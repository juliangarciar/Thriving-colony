#include <iostream>
#include <irrlicht.h>
#include "Input.h"

using namespace irr;
using namespace std;

int main() {

	// create device and exit if creation failed
	irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(1280, 720);
	IrrlichtDevice* device = createDeviceEx(params);
	
	if (device == 0) {
		return 1; // could not create selected driver.
	}

	/* The creation was successful, now we set the event receiver and
		store pointers to the driver and to the gui environment. */

	device -> setWindowCaption(L"Irrlicht Engine - Interface");
	device -> setResizable(true);

	video::IVideoDriver* driver = device -> getVideoDriver();
	scene::ISceneManager* smgr = device -> getSceneManager();
	gui::IGUIEnvironment* env = device -> getGUIEnvironment();

	
	//driver -> setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	// Add camera
	scene::ICameraSceneNode* camera =
		smgr -> addCameraSceneNodeFPS(0,100.0f,1.2f);

	/*camera -> setPosition(core::vector3df(2700*2,255*2,2600*2));
	camera -> setTarget(core::vector3df(2397*2,343*2,2700*2));
	camera -> setFarValue(42000.0f);*/

	// Draw terrain
	scene::ITerrainSceneNode* terrain = smgr -> addTerrainSceneNode(
		"terrain-heightmap.bmp",
		0,										// parent node
		-1,										// node id
		core::vector3df(0.f, 0.f, 0.f),			// position
		core::vector3df(0.f, 0.f, 0.f),			// rotation
		core::vector3df(40.f, 4.4f, 40.f),		// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,										// maxLOD
		scene::ETPS_17,							// patchSize
		4										// smoothFactor
	);
	
	/*terrain -> setMaterialFlag(video::EMF_LIGHTING, false);

	terrain -> setMaterialTexture(0, driver -> getTexture("terrain-texture.jpg"));
	terrain -> setMaterialTexture(1, driver -> getTexture("detailmap3.jpg"));
	terrain -> setMaterialType(video::EMT_DETAIL_MAP);
	terrain -> scaleTexture(1.0f, 20.0f);*/

	// Cursor terrain
    scene::ITriangleSelector* selector = smgr -> createTerrainTriangleSelector(terrain);
    terrain -> setTriangleSelector(selector);
	gui::ICursorControl *cursor = device -> getCursorControl();
    scene::ISceneCollisionManager* collisionManager = smgr -> getSceneCollisionManager();
	scene::ISceneNode* sphere = smgr -> addSphereSceneNode();

	
	// Add cube in the scene
	/*scene::IMesh* cube = smgr -> getGeometryCreator() -> createCubeMesh();
    scene::IMeshSceneNode *cubeNode = smgr -> addCubeSceneNode(100);

    if(cubeNode) {
        cubeNode -> setMaterialFlag(video::EMF_LIGHTING, false);
        cubeNode -> setPosition(core::vector3df(500,500,500));
	}*/
	
	// Font and Text of Interface
	/*gui::IGUISkin* skin = env -> getSkin();
	gui::IGUIFont* font = env -> getFont("fonthaettenschweiler.bmp");
	if (font)
		skin -> setFont(font);

	skin -> setFont(env -> getBuiltInFont(), gui::EGDF_TOOLTIP);*/

    // Add the buttons
	/*env -> addButton(core::rect<s32>(core::position2d<s32>(540, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_QUIT_BUTTON,
			L"Quit", L"Exits Program");
	env -> addButton(core::rect<s32>(core::position2d<s32>(540, 350), core::dimension2d<s32>(200, 60)), 0, GUI_ID_NEW_WINDOW_BUTTON,
			L"New Window", L"Launches a new Window");
	env -> addButton(core::rect<s32>(core::position2d<s32>(1040, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_FILE_OPEN_BUTTON,
			L"File Open", L"Opens a file");*/


	// Store the appropriate data in a context structure.
	//SAppContext context;
	//context.device = device;
	//context.counter = 0;
	//context.listbox = listbox;

	// Then create the event receiver, giving it that context structure.
	// El receptor guarda la informacion de las teclas pulsadas
	Input receiver;

	// Call
	receiver.Terrain(device, driver, smgr, env, camera, terrain, selector, cursor, collisionManager, sphere);

	// And tell the device to use our custom event receiver.
	// Decirle al dispositivo que use nuestro receptor de eventos personalizados.
	device -> setEventReceiver(&receiver);


	/* LOGO */
	/*env -> addImage(driver -> getTexture("Starcraft2.png"),
			core::position2d<int>(10,10));*/


	while(device -> run() && driver) {
		if (device -> isWindowActive()) {
			
			driver -> beginScene(true, true, 0);
			
			/*core::position2d<s32> pos = cursor -> getPosition();

			core::vector3df point;
			core::triangle3df triangle;

			scene::ISceneNode *node = 0;
			const core::line3d<f32> ray = collisionManager -> getRayFromScreenCoordinates(pos);
			if (collisionManager -> getCollisionPoint (ray, selector, point, triangle, node)) {
				sphere -> setPosition(point);
				cout<< triangle.pointA.X << " " << triangle.pointA.Y << " " << triangle.pointA.Z <<endl;
				cout<<"funciona ???"<<endl;
			}*/

			smgr -> drawAll();
			env -> drawAll();
		
			driver -> endScene();
		}
	}

	device -> drop();

	return 0;
}