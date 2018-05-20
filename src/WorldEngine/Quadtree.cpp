#include "Quadtree.h"
#include "Cell.h"
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>
#include <Building.h>
#include <Unit.h>

Quadtree::Quadtree(Vector2<f32> positionData, const Box2D& hitboxData, i32 deepValue):position(positionData),
                                                                                      hitBox(hitboxData),
                                                                                      depth(deepValue)                                                                               
{
    //std::cout << "I'm a Quadtree, and my deep is: " << deepValue <<  " and m y position is: " << positionData.x << "," << positionData.y << "\n";      
    //std::cout << "My hitbox is: " << hitboxData.Left() << "," << hitboxData.Top() << ":" << hitboxData.Right() << "," << hitboxData.Bottom() << "\n";                                                           
/* Initilize the innerCells */
    innerCells = std::vector<Cell*>();
/* If is not the last layer, create another one */
    if(depth != 0){
        innerTrees = std::vector<Quadtree*>(4);
        Vector2<f32> newTopLeft;
        Vector2<f32> newBottomRight;
        Vector2<f32> newCenter;
        Box2D newHitbox;
        f32 halfSize = (hitBox.Right() - hitBox.Left()) / 2; 
        i32 newDeep = depth - 1;
    /* Quad tree nº0 TopLeft*/
        newTopLeft = hitBox.TopLeft();
        newBottomRight = hitBox.Center();
        newCenter = (newTopLeft + newBottomRight) / 2.0f;
        newHitbox = Box2D(newTopLeft, newBottomRight);
        
        innerTrees[0] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº1 TopRight*/
        newTopLeft = Vector2<f32>(hitBox.Center().x, hitBox.Center().y - halfSize); 
        newBottomRight = Vector2<f32>(hitBox.Center().x + halfSize, hitBox.Center().y);
        newCenter = (newTopLeft + newBottomRight) / 2.0f;
        newHitbox = Box2D(newTopLeft, newBottomRight);
        
        innerTrees[1] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº2 BottomLeft*/
        newTopLeft = Vector2<f32>(hitBox.Center().x - halfSize, hitBox.Center().y);
        newBottomRight = Vector2<f32>(hitBox.Center().x, hitBox.Center().y + halfSize);
        newCenter = (newTopLeft + newBottomRight) / 2.0f;
        newHitbox = Box2D(newTopLeft, newBottomRight);

        innerTrees[2] = new Quadtree(newCenter, newHitbox, newDeep);
    /* Quad tree nº3 BottomRight*/
        newTopLeft = hitBox.Center();
        newBottomRight = hitBox.BottomRight();
        newCenter = (newTopLeft + newBottomRight) / 2.0f;
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
    if(this->depth == 0){
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
    if(this->depth == 0){
        for(std::size_t i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(buildingPtr->getHitbox()) && !innerCells[i]->isBlocked()){
                innerCells[i]->setInhabitingBuilding(buildingPtr);
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(buildingPtr->getHitbox())){
                innerTrees[i]->insertBuilding(buildingPtr);
            }
        }
    }
}

void Quadtree::clearBuilding(Building* buildingPtr){
    if(this->depth == 0){
        for(std::size_t i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(buildingPtr->getHitbox()) && innerCells[i]->getInhabitingBuilding() == buildingPtr){
                innerCells[i]->clearInhabitingBuilding();
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(buildingPtr->getHitbox())){
                innerTrees[i]->clearBuilding(buildingPtr);
            }
        }
    }
}

void Quadtree::assignNeighbors(Cell* cellPtr){
    if(this->depth == 0){
        Box2D tmp = cellPtr->getHitbox().getAmplifiedBox(2.0f);
        for(std::size_t i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(tmp)){
                if(innerCells[i] != cellPtr){
                    cellPtr->setNeighbor(innerCells[i]);
                }
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(cellPtr->getHitbox().getAmplifiedBox(2.0f))){
                innerTrees[i]->assignNeighbors(cellPtr);
            }
        }
    }
}

bool Quadtree::checkCollision(const Box2D& otherHitbox, bool isBuilding) const{
    bool newCenter = true;
    
    if(this->depth == 0){
        for(std::size_t i = 0; i < innerCells.size(); i++){
            if(isBuilding){
                if(innerCells[i]->getHitbox().isOverlappedWith(otherHitbox) && (innerCells[i]->isBlocked() || innerCells[i]->getTotalInhabitingUnits() > 0)){
                    newCenter = false;
                    return newCenter;
                }
            }
            else{
                if(innerCells[i]->getHitbox().isOverlappedWith(otherHitbox)){
                    if(innerCells[i]->getInhabitingBuilding() != nullptr){
                        if(innerCells[i]->getInhabitingBuilding()->getHitbox().isOverlappedWith(otherHitbox)){
                            newCenter = false;
                            return newCenter;
                        }
                    }
                }
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(otherHitbox)){
                newCenter = innerTrees[i]->checkCollision(otherHitbox, isBuilding);
                if(!newCenter){
                    return newCenter;
                }
            }
        }
    }
    return newCenter;
}

const Box2D& Quadtree::getHitbox() const{
    return hitBox;
}
const Vector2<f32> Quadtree::getPosition() const{
    return position;
}
/* Check this method, maybe ensure they are colliding, more precise but slower */
/* Is not working properly for some reason */
void Quadtree::getCollidingEntities(const Box2D& hitbox, Entity** priorityEntity, Enumeration::Team teamTarget) const{    
    if(this->depth == 0){
        for(std::size_t i = 0; i < innerCells.size(); i++){
            if(innerCells[i]->getHitbox().isOverlappedWith(hitbox)){
                std::vector< Unit* > unitTmp = innerCells[i]->getInhabitingUnits();
                if(!unitTmp.empty()){
                    for(std::size_t k = 0; k < unitTmp.size(); k++){
                        if(unitTmp[k]->getTeam() != teamTarget){
                            if(*priorityEntity == nullptr){
                                *priorityEntity = unitTmp[k];
                            }
                            else if(*priorityEntity != unitTmp[k]){
                                Vector2<f32> vectorDistance1 = (*priorityEntity)->getPosition() - hitbox.Center();
                                Vector2<f32> vectorDistance2 = unitTmp[k]->getPosition() - hitbox.Center();
                                if( (std::sqrt(std::pow(vectorDistance1.x, 2) + std::pow(vectorDistance1.y, 2))) > 
                                    (std::sqrt(std::pow(vectorDistance2.x, 2) + std::pow(vectorDistance2.y, 2))) ){
                                    *priorityEntity = unitTmp[k];
                                }
                            }
                        }
                    }
                }
                else{
                    Entity* buildingTmp = innerCells[i]->getInhabitingBuilding();
                    if(buildingTmp != nullptr){
                        if(buildingTmp->getTeam() != teamTarget){
                            if(*priorityEntity == nullptr){
                                *priorityEntity = buildingTmp;
                            }
                            else if((*priorityEntity)->getEntityType() == Enumeration::EntityType::Building && *priorityEntity != buildingTmp){
                                Vector2<f32> vectorDistance1 = (*priorityEntity)->getPosition() - hitbox.Center();
                                Vector2<f32> vectorDistance2 = buildingTmp->getPosition() - hitbox.Center();
                                if( (std::sqrt(std::pow(vectorDistance1.x, 2) + std::pow(vectorDistance1.y, 2))) > 
                                    (std::sqrt(std::pow(vectorDistance2.x, 2) + std::pow(vectorDistance2.y, 2))) ){
                                    *priorityEntity = buildingTmp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        for(i32 i = 0; i < 4; i++){
            if(innerTrees[i]->getHitbox().isOverlappedWith(hitbox)){
                innerTrees[i]->getCollidingEntities(hitbox, priorityEntity, teamTarget);
            }
        }
    }
}
