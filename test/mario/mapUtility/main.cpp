#include <GraphicEngine/Window.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/IO.h>

i32 main() {
    Window *w = Window::Instance();
    IO *io = IO::Instance();
    
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/map/map.json");

    json j = *r -> getJSON();

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["size"]["x"].get<int>(), j["map"]["size"]["y"].get<int>(), j["map"]["size"]["z"].get<int>()));
    

    while (w -> isOpen()){
        io->getMouse()->refreshStates();

        w -> beginScene();
        w -> endScene();
    }

    w -> close();
    
    return 0;
}