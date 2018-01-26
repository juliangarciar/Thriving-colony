#include <GLFW/glfw3.h>

#include <irrlicht.h>
#include <nanogui/nanogui.h>

#include <GraphicEngine/Window.h>
#include <GraphicEngine/Terrain.h>
#include <CameraController.h>

#include <iostream>

int main(int argc, char **argv) {
    Window *w = Window::Instance();

    InputManager *io = new InputManager();

    Terrain *map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
    map -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map

    CameraController *camera = new CameraController(map);

    scene::IMeshSceneNode *cube;
    cube = w -> getSceneManager() -> addCubeSceneNode(10);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    cube -> setPosition(core::vector3df(0, 0, 0));

    // Create nanogui gui
    w -> getGUIEnvironment() -> add<nanogui::Button>("Hola");

    cube = w -> getSceneManager() -> addCubeSceneNode(10);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    cube -> setPosition(core::vector3df(10, 10, 10));
   
    w -> getGUIEnvironment() -> setVisible(true);
    w -> getGUIEnvironment() -> performLayout();

    cube = w -> getSceneManager() -> addCubeSceneNode(10);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    cube -> setPosition(core::vector3df(20, 20, 20));

    while (w -> isOpen()){
        w -> beginScene();

        w -> endScene();
    }

    w -> close();
}