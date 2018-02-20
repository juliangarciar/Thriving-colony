#include "CellSpacePartition.h"
Cell::Cell(Vector2<f32> topLeft, Vector2<f32> botRight){
    BBox = Box2D(topLeft, botRight);
    blocked = true;
    mainRoad = false;
    inhabitingBuilding = 0;
}
Cell::~Cell(){
    inhabitingUnits.clear();
    nearNeighbors.clear();
}
void Cell::setBlocked(bool data){
    blocked = data;
}
void Cell::setMainRoad(bool data){
    mainRoad = data;
}
void Cell::setInhabitingBuilding(Entity* building){
    inhabitingBuilding = building;
    blocked = true;
}
void Cell::setInhabitingUnit(Entity* unit){
    inhabitingUnits.push_back(unit);
}
void Cell::setNearNeighbor(Cell* neighbor){
    nearNeighbors.push_back(neighbor);
}
void Cell::setIndex(i32 data){
    index = data;
}
void Cell::clearBuilding(){
    inhabitingBuilding = 0;
    blocked = false;
}
void Cell::clearUnit(Entity* unit){
    for(i32 i = 0; i < inhabitingUnits.size(); i++){
        if(inhabitingUnits.at(i) == unit){
            inhabitingUnits.erase(inhabitingUnits.begin() + i);
        }
    }
}
void Cell::Clear(){
    inhabitingBuilding = 0;
    inhabitingUnits.clear();
    //blocked = true;
    mainRoad = false;
}
bool Cell::isBlocked(){
    return blocked;
}
bool Cell::isMainRoad(){
    return mainRoad;
}
bool Cell::canBuild(){
    if(!blocked && !mainRoad)
        return true;
    else
        return false;
}
Box2D Cell::getHitBox(){
    return BBox;
}
Entity* Cell::getInhabitingBuilding(){
    return inhabitingBuilding;
}
std::vector< Entity* > Cell::getInhabitingUnits(){
    return inhabitingUnits;
}
std::vector< Cell* > Cell::getNearNeighbors(){
    return nearNeighbors;
}
i32 Cell::getIndex(){
    return index;
}
CellSpacePartition::CellSpacePartition(i32 width, i32 height, i32 spaceX, i32 spaceY)
{
    mapX = width;
    mapY = height;
    cellX = spaceX;
    cellY = spaceY;
    //calculate bounds of each cell
    nCellsX = mapX / cellX;
    nCellsY = mapY / cellY;
    //create the cells
    std::cout << "Inicializando celulas \n";
    for (i32 y = 0; y < nCellsY; y++)
    {
        for (i32 x = 0; x < nCellsX; x++)
        {
            f32 left  = x * cellX;
            f32 right = left + cellX;
            f32 top   = y * cellY;
            f32 bot   = top + cellY;
            Cell* tmp = new Cell(Vector2<f32>(left, top), Vector2<f32>(right, bot));
            tmp -> setIndex(y * nCellsY + x);
            mCells.push_back(tmp);
        }
    }
    i32 max = mCells.size();
    for(i32 y = 0; y < nCellsY; y++){
        for(i32 x = 0; x < nCellsX; x++){
            Cell* tmp = mCells.at(nCellsY * y + x);
            if(y == 0){
                if(x == 0){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(nCellsX));
                    tmp->setNearNeighbor(mCells.at(nCellsX + 1));
                }
                else if(x == nCellsX - 1){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(2 * tmp->getIndex()));
                }
                else{
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(2 * tmp->getIndex()));
                    tmp->setNearNeighbor(mCells.at(2 * tmp->getIndex() + 1));
                }
            }
            else if(y == nCellsY - 1){
                if(x == 0){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX + 1));
                }
                else if(x == nCellsX - 1){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX - 1));
                }
                else{
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX + 1));
                }
            }
            else{
                if(x == 0){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX + 1));
                }
                else if(x == nCellsX - 1){
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX));
                }
                else{
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - nCellsX + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX - 1));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX));
                    tmp->setNearNeighbor(mCells.at(tmp->getIndex() + nCellsX + 1));
                }
            }
        }
    }
    std::cout << "Number of cells " << mCells.size() << "\n";
}

CellSpacePartition::~CellSpacePartition(){
    this->mNeighbors.clear();
    this->mCells.clear();
}

void CellSpacePartition::updateUnitCell(Entity* unit, Vector2<f32> oldPos)
{
    Vector2<f32> newPos = unit->getPosition()->toVector2();
    if (sameCell(oldPos, newPos)) return;

    positionToCell(oldPos)->clearUnit(unit);
    positionToCell(newPos)->setInhabitingUnit(unit);
}

void CellSpacePartition::updateBuildingCell(Entity *object){
    if(object != NULL){
        Vector2<f32> storage = object -> getPosition() -> toVector2();
        if(object -> getCells() % 2 == 0){
            storage.x -= cellX / 2;
            storage.y -= cellY / 2;
            storage.x -= (object -> getCells() / 2) * (cellX / 2);
            storage.y -= (object -> getCells() / 2) * (cellY / 2);
        }
        else{
            storage.x -= (object -> getCells() - 1) * (cellX / 2);
            storage.y -= (object -> getCells() - 1) * (cellY / 2);
        }
        for(i32 i = 0; i < object -> getCells(); i++){
            for(i32 j = 0; j < object->getCells(); j++){
                positionToCell(Vector2<f32>(storage.x + cellX * i, storage.y + cellY * j))->setInhabitingBuilding(object);
                std::cout << "Colision creada en: " << i << "," << j << "\n";
            }
        }
    }
}
void CellSpacePartition::clearCells(){
    for(i32 i = 0; i < mCells.size(); i++){
        mCells.at(i)->Clear();
    }
}
Vector3<f32> CellSpacePartition::correctBuildingPosition(Vector3<f32> targetPos, Entity *object, bool &collision){
    Vector3<f32> correctOne = Vector3<f32>();
    if(object != NULL){
        Cell* dummy = positionToCell(targetPos.toVector2());
        Vector2<f32> storage;
        if(object -> getCells() % 2 == 0){
            storage = dummy->getHitBox().TopLeft();
            correctOne.x = storage.x;
            correctOne.z = storage.y;
            storage.x -= cellX / 2;
            storage.y -= cellY / 2;
            storage.x -= (object -> getCells() / 2) * (cellX / 2);
            storage.y -= (object -> getCells() / 2) * (cellY / 2);
        }
        else{
            storage = dummy->getHitBox().Center();
            correctOne.x = storage.x;
            correctOne.z = storage.y;
            storage.x -= (object -> getCells() - 1) * (cellX / 2);
            storage.y -= (object -> getCells() - 1) * (cellY / 2);
        }
        for(i32 i = 0; i < object -> getCells() && collision == false; i++){
            for(i32 j = 0; j < object->getCells() && collision == false; j++){
                if(!positionToCell(Vector2<f32>(storage.x + cellX * i, storage.y + cellY * j))->canBuild()){
                    collision = true;
                    std::cout << "Colision \n";
                }
            }
        }
    }
    return correctOne;
}
//bool CellSpacePartition::checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition){
//
//    std::vector< Entity* > totalNeighbors;
//    Cell* idx = positionToCell(targetPosition);
//    std::vector< Cell* > neighbors = idx->getNearNeighbors();
//    if(idx != NULL && idx->isBlocked()){
//        return false;
//    }
//    else{
//        for(i32 i = 0; i < neighbors.size(); i++){
//            if(neighbors.at(i)->getInhabitingBuilding() != 0){
//                //totalNeighbors.push_back(neighbors.at(i).getInhabitingBuilding);
//                std::cout << "Existen entidades cercanas.\n";
//            }
//        }
//        return true;
//    }
//}
bool CellSpacePartition::isBlocked(Vector2<f32> targetPos){
    Cell* dummy = positionToCell(targetPos);
    if(dummy != NULL)
        return dummy->isBlocked();
    else
        return true;
}
bool CellSpacePartition::sameCell(Vector2<f32> oldPos, Vector2<f32> newPos){
    Cell* oldCell = positionToCell(oldPos);
    Cell* newCell = positionToCell(newPos);
    if(oldCell == newCell)
        return true;
    else 
        return false;
}
Cell* CellSpacePartition::positionToCell(Vector2<f32> pos){
    int dummy = (i32)(nCellsX * pos.x / mapX) + 
                ((i32)((nCellsY) * pos.y / mapY) * nCellsY);
    if(dummy < 0 || dummy > mCells.size()){
        return NULL;
    }
    i32 idx = dummy;

    if (idx == mCells.size()) 
        idx = mCells.size() - 1;

    return mCells.at(idx);
}