#include <GraphicEngine/Window.h>
#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>
#include <IOEngine/IO.h>
#include "CameraController.h"

i32 main() {
    std::vector<Light*> lights;
    Vector3<f32> collisionPoint;

    Window *w = Window::Instance();
    IO *io = IO::Instance();

    io -> getResourceManager() -> loadResource("map/map.json");
    
    ResourceJSON *r = (ResourceJSON*)io -> getResourceManager() -> getResource("map/map.json");

    json j = *r -> getJSON();

    //Create map
    Terrain *terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["size"]["x"].get<int>(), j["map"]["size"]["y"].get<int>(), j["map"]["size"]["z"].get<int>()));
    
    //Luz
    for (auto& element : j["lights"]){
        Vector3<f32> lp;
        lp.x = element["position"]["x"].get<int>();
        lp.z = element["position"]["z"].get<int>();
        lp.y = terrain -> getY(lp.x, lp.z) + element["height"].get<int>();
        Light *light = new Light(lp, element["intensity"].get<int>()); 
        lights.push_back(light);
    }

    //Init camera controller
    CameraController *camera = new CameraController();
    camera -> setZoomDistanceFromTarget(j["camera"]["zoomDistanceFromTarget"].get<int>());
    camera -> setRotateDegrees(j["camera"]["delta_x"].get<int>(), j["camera"]["delta_y"].get<int>());
    camera -> Init(Vector3<float>(4000, 800, 4000));
   
    while (w -> isOpen()){
        camera -> Move();
        camera -> RotateAndInclinate();
        camera -> Zoom();

        collisionPoint = terrain->getPointCollision(IO::Instance()->getMouse());
        
        io->getMouse()->refreshStates();

        camera -> Update(Window::Instance() -> getDeltaTime(), terrain);

        w -> beginScene();
        w -> endScene();
    }

    w -> close();
    
    return 0;
}