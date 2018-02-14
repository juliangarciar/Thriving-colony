#include "CellSpacePartition.h"
#define MAX_MAP 10240
#define TOTAL 80
#define RADIOUS 64

Cell::~Cell(){
    this->entities.clear();
    //delete cube;
}
CellSpacePartition* CellSpacePartition::pinstance = 0;

CellSpacePartition* CellSpacePartition::Instance() {
    if(pinstance == 0) {
        pinstance = new CellSpacePartition();
    }
    return pinstance;
}

CellSpacePartition::CellSpacePartition()
{
    mCells.reserve(TOTAL * TOTAL);
    //mNeighbors.reserve(9);
    //calculate bounds of each cell
    cellSizeX = MAX_MAP / TOTAL;
    cellSizeY = MAX_MAP / TOTAL;
    //create the cells
    for (i32 y = 0; y < TOTAL; y++)
    {
        for (i32 x = 0; x < TOTAL; x++)
        {
            f32 left  = x * cellSizeX;
            f32 right = left + cellSizeX;
            f32 top   = y * cellSizeY;
            f32 bot   = top + cellSizeY;
            //f32 center = left + cellSizeX / 2;
            //f32 center2 = top - cellSizeY / 2;
            mCells.push_back(Cell(Vector2<f32>(left, top), Vector2<f32>(right, bot)));
        }
    }
    std::cout << "Number of cells " << mCells.size() << "\n";
}

CellSpacePartition::~CellSpacePartition(){
    this->mNeighbors.clear();
    this->mCells.clear();
}
void CellSpacePartition::addEntity(Entity* ent)
{ 
    // Debugging only
    //assert (ent);

    //i32 sz = mCells.size();
    Vector2<f32> dummy = ent->getPosition()->toVector2();
    i32 idx = positionToIndex(dummy);
    
    mCells[idx].entities.push_back(ent);
}
// Edit
// Maybe this need to be deleted, not doing anything good
void CellSpacePartition::removeEntity(Entity* ent, Vector2<f32> position){
    i32 idx = positionToIndex(position);
    if(idx < mCells.size() && idx != -1)
    {   
        std::list< Entity* >::iterator it;
        for (it = mCells.at(idx).entities.begin(); it != mCells.at(idx).entities.end(); it++){
            std::cout << "Petas \n";
            if(*it == ent){
                mCells.at(idx).entities.erase(it);
                break;
            }
        }
    }
}

std::vector< Entity* > CellSpacePartition::calculateNeighbors(Vector2<f32> targetPos){
    Vector2<f32> dummy;
    std::vector< Entity* > objects;
    dummy.x = targetPos.x - cellSizeX;
    dummy.y = targetPos.y + cellSizeY;
    Vector2<f32> magical;
    i32 idx = -1;
    bool done = false;
    for(i32 i = 0; i < 3; i++){
        for(i32 j = 0; j < 3; j++){
            magical.x = dummy.x + cellSizeX * i;
            magical.y = dummy.y + cellSizeY * j;
            idx = positionToIndex(magical);
            // Fix this shit
            if(idx != -1 && idx < mCells.size()){
                if(!mCells.at(idx).entities.empty()){
                    done = false;
                    //if(objects.empty()){
                        objects.push_back(mCells.at(idx).entities.back());
                    //}
                    //else{
                        //for(i32 z = 0; z < objects.size() && done == false; z++){
                        //    if(objects.at(z) == mCells.at(idx).entities.back()){
                        //        done = true;
                        //    }
                        //}
                        //if(!done){
                        //    objects.push_back(mCells.at(idx).entities.back());
                        //}
                   // }
                }
            }
        }
    }
    return objects;
}

void CellSpacePartition::updateEntity(Entity* ent, Vector2<f32> OldPos)
{
    //if the index for the old pos and the new pos are not equal then
    //the T has moved to another cell.
    i32 OldIdx = positionToIndex(OldPos);
    i32 NewIdx = positionToIndex(ent->getPosition()->toVector2());

    if (NewIdx == OldIdx) return;

    //the T has moved into another cell so delete from current cell
    //and add to new one
    // Edit this shit
    removeEntity(ent, OldPos);
    //mCells[OldIdx].entities.remove(ent);
    mCells[NewIdx].entities.push_back(ent);
}

void CellSpacePartition::updateCell(Entity *object){
    if(object != NULL){
        Vector2<f32> storage = object -> getPosition() -> toVector2();
        if(object -> getCells() % 2 == 0){
            storage.x -= cellSizeX / 2;
            storage.y -= cellSizeY / 2;
            storage.x -= (object -> getCells() / 2) * (cellSizeX / 2);
            storage.y -= (object -> getCells() / 2) * (cellSizeY / 2);
        }
        else{
            storage.x -= (object -> getCells() - 1) * (cellSizeX / 2);
            storage.y -= (object -> getCells() - 1) * (cellSizeY / 2);
        }
        for(i32 i = 0; i < object -> getCells(); i++){
            for(i32 j = 0; j < object->getCells(); j++){
                mCells.at(positionToIndex(Vector2<f32>(storage.x + cellSizeX * i, storage.y + cellSizeY * j))).entities.push_back(object);
                std::cout << "Colision creada en: " << i << "," << j << "\n";
            }
        }
    }
}

i32 CellSpacePartition::positionToIndex(Vector2<f32> pos)
{
    int dummy = (i32)(TOTAL * pos.x / MAX_MAP) + 
                ((i32)((TOTAL) * pos.y / MAX_MAP) * TOTAL);
    if(dummy < 0 || dummy > mCells.size()){
        return -1;
    }
    i32 idx = dummy;

    // Maybe this explode
    if (idx == mCells.size()) 
        idx = mCells.size() - 1;

    return idx;
}

Vector3<f32> CellSpacePartition::correctPosition(Vector3<f32> targetPos, Entity *object, bool &collision){
    Vector3<f32> correctOne = Vector3<f32>();
    if(object != NULL){
        Cell dummy = mCells.at(positionToIndex(targetPos.toVector2()));
        Vector2<f32> storage;
        if(object -> getCells() % 2 == 0){
            storage = dummy.BBox.TopLeft();
            correctOne.x = storage.x;
            correctOne.z = storage.y;
            storage.x -= cellSizeX / 2;
            storage.y -= cellSizeY / 2;
            storage.x -= (object -> getCells() / 2) * (cellSizeX / 2);
            storage.y -= (object -> getCells() / 2) * (cellSizeY / 2);
        }
        else{
            storage = dummy.BBox.Center();
            correctOne.x = storage.x;
            correctOne.z = storage.y;
            storage.x -= (object -> getCells() - 1) * (cellSizeX / 2);
            storage.y -= (object -> getCells() - 1) * (cellSizeY / 2);
        }
        for(i32 i = 0; i < object -> getCells() && collision == false; i++){
            for(i32 j = 0; j < object->getCells() && collision == false; j++){
                if(!mCells.at(positionToIndex(Vector2<f32>(storage.x + cellSizeX * i, storage.y + cellSizeY * j))).entities.empty()){
                    collision = true;
                    std::cout << "Colision \n";
                }
            }
        }
    }
    return correctOne;
}
bool CellSpacePartition::checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition){
    //Vector2<f32> dummy = origin;
    //Box2D box = Box2D(dummy - Vector2<f32>(RADIOUS, 0), dummy + Vector2<f32>(0, RADIOUS));
    //dummy = targetPosition - box.Center();
    //dummy = dummy / 2;
    //if(!mCells.at(positionToIndex(box.TopLeft() + dummy)).entities.empty())
    //    return true;
    //
    //else if(!mCells.at(positionToIndex(box.BottomRight() + dummy)).entities.empty())
    //    return true;

    //else if(!mCells.at(positionToIndex(box.TopRight() + dummy)).entities.empty())
    //    return true;

    //else if(!mCells.at(positionToIndex(box.BottomLeft() + dummy)).entities.empty())
    //    return true;

    //return false;
    std::vector< Entity* > totalNeighbors;
    i32 idx = positionToIndex(targetPosition);
    if(idx != -1 && mCells.at(idx).entities.empty()){
        
        return false;
    }
    else{
        totalNeighbors = calculateNeighbors(origin);
        if(!totalNeighbors.empty()){
            std::cout << "Existen: " << totalNeighbors.size() << " entidades cercanas.\n";
        }
        return true;
    }
}
bool CellSpacePartition::isBlocked(Vector2<f32> targetPos){
    Cell dummy = mCells.at(positionToIndex(targetPos));
    if(dummy.entities.empty())
        return false;
    else
        return true;
}

