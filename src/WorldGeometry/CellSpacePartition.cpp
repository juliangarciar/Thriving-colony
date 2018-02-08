#include "CellSpacePartition.h"
#define MAX_MAP 10240
#define CELL_SPACE 128
Cell::~Cell(){
    this->entities.clear();
    //delete cube;
}
CellSpacePartition::CellSpacePartition( f32  width,        //width of 2D space
                                        f32  height,       //height...
                                        i32    nCellsX,       //number of divisions horizontally
                                        i32    nCellsY,       //and vertically
                                        i32    MaxTs):  //maximum number of entities to partition
                    spaceWidth(width),
                    spaceHeight(height),
                    cellsX(nCellsX),
                    cellsY(nCellsY),
                    mNeighbors(MaxTs)
{
//calculate bounds of each cell
    cellSizeX = width  / cellsX;
    cellSizeY = height / cellsY;
//create the cells
    for (i32 y = 0; y < 1; y++)
    {
        for (i32 x = 0; x < 4; x++)
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
}
CellSpacePartition::~CellSpacePartition(){
    this->mNeighbors.clear();
    this->mCells.clear();
}
void CellSpacePartition::calculateNeighbors(Vector2<f32> targetPos, f32 radious){
    std::vector< Entity* >::iterator itNeighbor = mNeighbors.begin();

    Box2D queryBox(targetPos - Vector2<f32>(radious, radious), targetPos + Vector2<f32>(radious, radious));
    std::vector< Cell >::iterator itCell;
    for(itCell = mCells.begin(); itCell != mCells.end(); itCell++){
        if(itCell->BBox.isOverlappedWith(queryBox) && !itCell->entities.empty()){
            // Call the method begin instead
            std::list< Entity* >::iterator it; 
            for(it = itCell->entities.begin(); it != itCell->entities.end(); it++){
                // Complete this method
                if((*it)->getPosition()->toVector2().calculateDistance(targetPos) < (radious * radious)){
                    *itNeighbor++ = *it;
                }
            }
        }
    }
    *itNeighbor = 0;
}
void CellSpacePartition::clearCells()
{
    std::vector< Cell >::iterator it; 

    for (it = mCells.begin(); it != mCells.end(); it++)
    {
        it->entities.clear();
    }
}
i32 CellSpacePartition::positionToIndex(Vector2<f32> pos)
{
    i32 idx = (i32)(cellsX * pos.x / spaceWidth) + 
                ((i32)((cellsY) * pos.y / spaceHeight) * cellsX);

    if (idx > mCells.size() - 1) 
        idx = mCells.size() - 1;

    return idx;
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

void CellSpacePartition::updateEntity(Entity* ent, Vector2<f32> OldPos)
{
    //if the index for the old pos and the new pos are not equal then
    //the T has moved to another cell.
    i32 OldIdx = positionToIndex(OldPos);
    i32 NewIdx = positionToIndex(ent->getPosition()->toVector2());

    if (NewIdx == OldIdx) return;

    //the T has moved into another cell so delete from current cell
    //and add to new one
    mCells[OldIdx].entities.remove(ent);
    mCells[NewIdx].entities.push_back(ent);
}