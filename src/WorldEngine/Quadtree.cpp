#include "Quadtree.h"
#include "Cell.h"
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>
#include <Building.h>
Quadtree::Quadtree(Vector2<f32> positionData, Box2D hitboxData, i32 deepValue){
    position = positionData;
    hitBox = hitboxData;
    deep = deepValue;
    //std::cout << "I'm a Quadtree, and my deep is: " << deepValue <<  " and m y position is: " << positionData.x << "," << positionData.y << "\n";      
    //std::cout << "My hitbox is: " << hitboxData.Left() << "," << hitboxData.Top() << ":" << hitboxData.Right() << "," << hitboxData.Bottom() << "\n";                                                           
/* Initilize the innerCells */
    innerCells = std::vector<Cell*>();
/* If is not the last layer, create another one */
    if(deep != 0){
        innerTrees = std::vector<Quadtree*>(4);
        Vector2<f32> newTopLeft;
        Vector2<f32> newBottomRight;
        Vector2<f32> newCenter;
        Box2D newHitbox;
        f32 halfSize = (hitBox.Right() - hitBox.Left()) / 2; 
        i32 newDeep = deep - 1;
    /* Quad tree nº0 */
        newCenter = (hitBox.Center() + hitBox.TopLeft()) / 2;
        newTopLeft = hitBox.TopLeft();
        newBottomRight = hitBox.Center();
        newHitbox = Box2D(newTopLeft, newBottomRight);
        innerTrees[0] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº1 */
        newCenter = (hitBox.TopRight() - hitBox.Center()) / 2;
        newTopLeft.x += halfSize;
        newBottomRight.x += halfSize;
        newHitbox = Box2D(newTopLeft, newBottomRight);
        innerTrees[1] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº2 */
        newCenter = (hitBox.Center() - hitBox.BottomLeft()) / 2;
        newTopLeft.y += halfSize;
        newBottomRight.y += halfSize;
        newHitbox = Box2D(newTopLeft, newBottomRight);
        innerTrees[2] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº3 */
        newCenter = (hitBox.BottomRight() - hitBox.Center()) / 2;
        newTopLeft.x -= halfSize;
        newBottomRight.x -= halfSize;
        newHitbox = Box2D(newTopLeft, newBottomRight);
        innerTrees[3] = new Quadtree(newCenter, newHitbox, newDeep);
    }
}
Quadtree::~Quadtree(){
    for(i32 i = 0; i < 4; i++){
        delete innerTrees[i];
    }
    if(!innerCells.empty())
        innerCells.clear();
}
// ToDo: check this method
void Quadtree::Clear(){
    for(i32 i = 0; i < 4; i++){
        delete innerTrees[i];
    }
    if(!innerCells.empty())
        innerCells.clear();
}
void Quadtree::insertCell(Cell* cellPtr){
    if(this->deep == 0){
        innerCells.push_back(cellPtr);
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(cellPtr->getHitbox())){
                innerTrees[i]->insertCell(cellPtr);
                break;
            }
        }
    }
}
void Quadtree::insertBuilding(Building* buildingPtr){
    if(this->deep == 0){
        for(i32 i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(buildingPtr->getHit()) && innerCells[i]->getInhabitingBuilding() == NULL){
                innerCells[i]->setInhabitingBuilding(buildingPtr);
                innerCells[i]->setBlocked(true);
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(buildingPtr->getHit())){
                innerTrees[i]->insertBuilding(buildingPtr);
            }
        }
    }
}
void Quadtree::assignNeighbors(Cell* cellPtr){
    if(this->deep == 0){
        for(i32 i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(cellPtr->getHitbox().getAmplifiedBox(5.f))){
                if(innerCells[i] != cellPtr)
                    cellPtr->setNeighbor(innerCells[i]);
            }
        }
        //std::cout << "K vecinos = " << cellPtr->getNeighbors().size() << "\n";
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(cellPtr->getHitbox().getAmplifiedBox(5.f))){
                innerTrees[i]->assignNeighbors(cellPtr);
            }
        }
    }
}
bool Quadtree::canBuild(Box2D otherHitbox){
    bool newCenter = false;
    
    if(this->deep == 0){
        for(i32 i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(otherHitbox) && (innerCells[i]->getInhabitingBuilding() != NULL || innerCells[i]->isBlocked())){
                newCenter = true;
                return newCenter;
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(otherHitbox)){
                if(deep == 1){
                    //std::cout << "Estas en el Quadtree: " << i << "\n";
                }
                newCenter = innerTrees[i]->canBuild(otherHitbox);
                if(newCenter){
                    return newCenter;
                }
            }
        }
    }
    return newCenter;
}
Box2D Quadtree::getHitbox(){
    return hitBox;
}
Vector2<f32> Quadtree::getPosition(){
    return position;
}
