#include <iostream>
#include <queue>
#include <irrlicht.h>
#include "node.h"

using namespace std;
using namespace irr;

//TYPE NEEDED FOR PRIORITY QUEUE
struct comparePriority{
    bool operator()(node* const & p1, node* const & p2 ){
        return p1 -> getPriority() > p2 -> getPriority();
    }
};
//CHECK NEIGHBOURS
std::vector < node* > getNeighbours(node* currentData, node*** mapData){
    std::vector < node* > neighbours;
    i32 x = currentData -> getX();
    i32 y = currentData -> getY();
    if((x + 1) < 25){
        if(!mapData[x + 1][y] -> itsBlock())
        neighbours.push_back(mapData[x + 1][y]);
    }
    if((y + 1) < 25){
        if(!mapData[x][y + 1] -> itsBlock())
        neighbours.push_back(mapData[x][y + 1]);
    }
    if((x - 1) >= 0){
        if(!mapData[x - 1][y] -> itsBlock())
        neighbours.push_back(mapData[x - 1][y]);
    }
    if((y-  1) >= 0){
        if(!mapData[x][y - 1] -> itsBlock())
        neighbours.push_back(mapData[x][y - 1]);
    }
    return neighbours;
}
//MANHATTAN DISTANCE
i32 checkDistance(node* a, node* b){
    i32 x1 = a -> getX();
    i32 y1 = a -> getY();
    i32 x2 = b -> getX();
    i32 y2 = b -> getY();
    i32 distance = abs(x1 - x2) + abs(y1 - y2);
    return distance;
}
//MAIN FUNCTION
i32 main(){
    char insertKey;
    i32 clicks = 0;
    bool released = true;
    bool finish = false;
    i32 newCost = 0;
    i32 currentCost = 0;
    i32 priority = 0;
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
    
    //ADD IRRLICHT CAMERA
    scene::ICameraSceneNode *camera =
        smgr -> addCameraSceneNodeFPS();

        camera -> setPosition(core::vector3df(0, 500, 20));
        camera -> setTarget(core::vector3df(0, 0, 0));
        camera -> setFarValue(2000.0f);

    //INIT NEIGHBOURS DATA
    std::vector < node* > neighbors;
    //INIT MAP DATA
    node*** mapita = new node**[25];
    for (i32 x = 0; x < 25; x++)
    {
        mapita[x] = new node*[25];
        for (i32 y = 0; y < 25; y++)
        {
            mapita[x][y] = new node(x, y, smgr);
        }
    }
    //INIT FRONTIER DATA
    //std::queue< node* > frontier;
    std::priority_queue< node*, std::vector < node* >, comparePriority> frontier;

    //INIT START AND END
    node *start = mapita[4][5];
    start -> setCameFrom(NULL);
    start -> setWeight(0);
    node *end = mapita[18][13];

        start -> swapColor(irr::video::SColor(0, 0, 0, 255));
        end -> swapColor(irr::video::SColor(0, 255, 0, 0));

        //DRAW OBSTACLES
        for (i32 x = 13, y = 15; x < 20; x++, y--)
        {
            mapita[x][y] -> swapColor(irr::video::SColor(0, 0, 0, 0));
            mapita[x][y] -> setBlock(true);
    }
    //START FRONTIER
    node *current;
    frontier.push(start);


    //MAIN BUCLE
    while (device -> run())
    {
        if (device -> isWindowActive())
        {
            driver -> beginScene(true, true, 0);
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            //{

                //Start algorithm
                if (!finish)
                {

                    current = frontier.top();
                    //frontier.top() -> setVisited(true);
                    frontier.pop();
                    
                    //SHOW PATH
                    if (current == end)
                    {
                        cout << "Sansacabao" << endl;
                        finish = true;
                        end -> swapColor(irr::video::SColor(0, 255, 0, 0));

                        while (current != start)
                        {
                            current = current -> getCameFrom();
                            current -> swapColor(irr::video::SColor(0, 255, 0, 0));
                        }
                        //for (i32 x = 0; x < 25; x++)
                        //{
                        //    for (i32 y = 0; y < 25; y++)
                        //    {
                        //        window.draw(*mapita[x][y] -> getCube());
                        //    }
                        //}
                    }
                    neighbors = getNeighbours(current, mapita);
                    for (i32 i = 0; i < neighbors.size(); i++)
                    {
                        newCost = current -> getWeight() + 1;
                        if (!frontier.top() -> itsCounted() || newCost < neighbors[i] -> getWeight())
                        {
                            neighbors[i] -> swapColor(irr::video::SColor(0, 127, 0, 127));
                            neighbors[i] -> setWeight(newCost);
                            neighbors[i] -> setCounted(true);
                            priority = newCost + checkDistance(end, neighbors[i]);
                            neighbors[i] -> setPriority(priority);
                            frontier.push(neighbors[i]);
                            neighbors[i] -> setCameFrom(current);
                        }
                    }
                    neighbors.clear();
                }
            //for (i32 x = 0; x < 25; x++)
            //{
            //    for (i32 y = 0; y < 25; y++)
            //    {
            //        window.draw(*mapita[x][y] -> getRectangle());
            //    }
            //}
            smgr -> drawAll();
            driver -> endScene();
        }
    }

    while (!frontier.empty())
        frontier.pop();
    //neighbors.clear();

    delete start;
    delete end;
    delete current;

    for (i32 i = 0; i < 24; i++)
    {
        for (i32 j = 0; j < 24; j++)
        {
            delete mapita[i][j];
        }
        delete[] mapita[i];
    }

    delete[] mapita;
    return 0;
}