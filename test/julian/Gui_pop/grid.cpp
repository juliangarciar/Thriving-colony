#include "grid.h"
//Constructor
grid::grid(int x, int y, irr::scene::ISceneManager *smgrData)
{
    ox = x;
    oy = y;
    map = new nodeGrid**[ox];
    for (int i = 0; i < ox; i++){
        map[i] = new nodeGrid*[oy];
    }
    for (int i = 0; i < ox; i++){
        for (int j = 0; j < oy; j++){
            map[i][j] = new nodeGrid(i , j, smgrData);
        }
    }
}
grid::grid(const grid &orig){

}
//Delete
grid::~grid(){
    //Retocar 
    delete smgrData;
    for(int i = 0; i < ox; i++){
        for(int j = 0; j < oy; j++){
            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
//Manhattan distance
int grid::checkDistance(nodeGrid* a, nodeGrid* b){
    int x1 = a->getX();
    int y1 = a->getY();
    int x2 = b->getX();
    int y2 = b->getY();
    int distance = abs(x1 - x2) + abs(y1 - y2);
    return distance;
}
std::vector< nodeGrid* > grid::getNeighbours(nodeGrid* currentData){
    std::vector < nodeGrid* > neighbours;
    int x = currentData->getX();
    int y = currentData->getY();
    if((x + 1) < 25){
        if(!map[x + 1][y]->itsBlock())
        neighbours.push_back(map[x + 1][y]);
    }
    if((y + 1) < 25){
        if(!map[x][y + 1]->itsBlock())
        neighbours.push_back(map[x][y + 1]);
    }
    if((x - 1) >= 0){
        if(!map[x - 1][y]->itsBlock())
        neighbours.push_back(map[x - 1][y]);
    }
    if((y-  1) >= 0){
        if(!map[x][y - 1]->itsBlock())
        neighbours.push_back(map[x][y - 1]);
    }
    return neighbours;
}