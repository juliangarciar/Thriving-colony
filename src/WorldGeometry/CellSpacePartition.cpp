#include "CellSpacePartition.h"

Cell::~Cell(){
    this->entities.clear();
    //delete cube;
}
CellSpacePartition::CellSpacePartition( float  width,        //width of 2D space
                                        float  height,       //height...
                                        int    nCellsX,       //number of divisions horizontally
                                        int    nCellsY,       //and vertically
                                        int    MaxTs):  //maximum number of entities to partition
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
    for (int y = 0; y < 1; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            float left  = x * cellSizeX;
            float right = left + cellSizeX;
            float top   = y * cellSizeY;
            float bot   = top + cellSizeY;
            //float center = left + cellSizeX / 2;
            //float center2 = top - cellSizeY / 2;
            mCells.push_back(Cell(Vector2<float>(left, top), Vector2<float>(right, bot)));
        }
    }
}
CellSpacePartition::~CellSpacePartition(){
    this->mNeighbors.clear();
    this->mCells.clear();
}
void CellSpacePartition::calculateNeighbors(Vector2<float> targetPos, float radious){
    std::vector< Entity* >::iterator itNeighbor = mNeighbors.begin();

    Box2D queryBox(targetPos - Vector2<float>(radious, radious), targetPos + Vector2<float>(radious, radious));
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
int CellSpacePartition::positionToIndex(Vector2<float> pos)
{
    int idx = (int)(cellsX * pos.x / spaceWidth) + 
                ((int)((cellsY) * pos.y / spaceHeight) * cellsX);

    if (idx > mCells.size() - 1) 
        idx = mCells.size() - 1;

    return idx;
}

void CellSpacePartition::addEntity(Entity* ent)
{ 
    // Debugging only
    //assert (ent);

    //int sz = mCells.size();
    Vector2<float> dummy = ent->getPosition()->toVector2();
    int idx = positionToIndex(dummy);
    
    mCells[idx].entities.push_back(ent);
}

void CellSpacePartition::updateEntity(Entity* ent, Vector2<float> OldPos)
{
    //if the index for the old pos and the new pos are not equal then
    //the T has moved to another cell.
    int OldIdx = positionToIndex(OldPos);
    int NewIdx = positionToIndex(ent->getPosition()->toVector2());

    if (NewIdx == OldIdx) return;

    //the T has moved into another cell so delete from current cell
    //and add to new one
    mCells[OldIdx].entities.remove(ent);
    mCells[NewIdx].entities.push_back(ent);
}