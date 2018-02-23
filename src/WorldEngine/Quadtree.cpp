#include "Quadtree.h"
#include "Cell.h"
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>
Quadtree::Quadtree(Vector2<f32>& position, i32 length, i32 width, i32 deepValue){
    Vector2<f32> topLeft;
    topLeft.x = position.x - width / 2;
    topLeft.y = position.y - length / 2;
    Vector2<f32> botRight;
    botRight.x = position.x + width / 2;
    botRight.y = position.y + length / 2;
    hitBox = Box2D(topLeft, botRight);
    deep = deepValue;
    innerCells = std::vector<Cell*>();
    if(deep != 0){
        innerTrees = std::vector<Quadtree*>(4);
        f32 halfSizeX = width / 2;
        f32 halfSizeY = length / 2;
        for(i32 i = 0; i < 2; i++){
            for(i32 j = 0; j < 2; j++){
                Vector2<f32> tmp;
                tmp.x = (i * halfSizeX) + (halfSizeX / 2); 
                tmp.y = (j * halfSizeY) + (halfSizeY / 2);
                innerTrees[i] = new Quadtree(&tmp, halfSizeX, halfSizeY, deep--);
            }
        }
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
bool Quadtree::insertCell(Cell* cellPtr){
    if(this->deep == 0){
        innerCells.push_back(cellPtr);
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(cellPtr->getHitBox())){
                innerTrees[i]->insertCell(cellPtr);
                break;
            }
        }
    }
}
bool Quadtree::canBuild(Box2D& otherHitbox){
    bool tmp = true;
    if(this->deep == 0){
        for(i32 i = 0; i < innerCells.size(); i++){
            if(innerCells[i].getHitbox().isOverlappedWith(otherHitbox)){
                tmp = false;
                return tmp;
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(otherHitbox)){
                tmp = innerTrees[i]->canBuild(otherHitbox);
                if(!tmp){
                    return tmp;
                }
            }
        }
    }
    return tmp;
}
Box2D& Quadtree::getHitbox(){
    return hitBox;
}
