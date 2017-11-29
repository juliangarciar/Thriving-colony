#include "Grid.h"
#include "NodeGrid.h"
//Constructor
grid::grid(int x, int y, irr::scene::ISceneManager *smgrData)
{
    ox = x;
    oy = y;
    map = new nodeGrid **[ox];
    for (int i = 0; i < ox; i++)
    {
        map[i] = new nodeGrid *[oy];
    }
    for (int i = 0; i < ox; i++)
    {
        for (int j = 0; j < oy; j++)
        {
            map[i][j] = new nodeGrid(i, j, 0, smgrData);
        }
    }
}
grid::grid(const grid &orig)
{
}
//Delete
grid::~grid()
{
    //Retocar
    delete smgrData;
    for (int i = 0; i < ox; i++)
    {
        for (int j = 0; j < oy; j++)
        {
            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
//Manhattan distance
float grid::checkDistance(nodeGrid *a, nodeGrid *b, nodeGrid *startData)
{
    //int dx1 = b->getX() - a->getX();
    //int dy1 = b->getY() - a->getY();
    //int dx2 = startData->getX() - a->getX();
    //int dy2 = startData->getY() - a->getY();
    //int cross = abs(dx1 * dy2 - dx2 * dy1);
    //heuristic += cross * 0.001

    float dx = abs(a->getX() - b->getX());
    float dy = abs(a->getY() - b->getY());
    float twoD = sqrt(2);
    int oneD = 1;
    float result = oneD * (dx + dy) + (twoD - 2 * oneD) * std::min(dx, dy);
    //result += cross * 1.001;
    return result;
    //return abs(a->getX() - b->getX()) + abs(a->getY() - b->getY());
}
std::vector<nodeGrid *> grid::getNeighbours(nodeGrid *currentData)
{
    std::vector<nodeGrid *> neighbours;
    int x = currentData->getX();
    int y = currentData->getY();
    //Right node
    if ((x + 1) < this->ox && (x + 1) >= 0)
    {
        if (!map[x + 1][y]->itsBlock())
        {
            neighbours.push_back(map[x + 1][y]);
        }
    }
    //Left node
    if ((x - 1) >= 0 && (x - 1) < this->ox)
    {
        if (!map[x - 1][y]->itsBlock())
        {
            neighbours.push_back(map[x - 1][y]);
        }
    }
    //Bottom node
    if ((y + 1) < this->oy && (y + 1) >= 0)
    {
        if (!map[x][y + 1]->itsBlock())
        {
            neighbours.push_back(map[x][y + 1]);
        }
    }
    //Top node
    if ((y - 1) >= 0 && (y - 1) < this->oy)
    {
        if (!map[x][y - 1]->itsBlock())
        {
            neighbours.push_back(map[x][y - 1]);
        }
    }
    //Top-left node
    if ((y - 1 < this->oy) && (y - 1 >= 0) && (x - 1 < this->ox) && (x - 1 >= 0))
    {
        if (!map[x - 1][y - 1]->itsBlock())
        {
            map[x - 1][y - 1]->setDiag(true);
            neighbours.push_back(map[x - 1][y - 1]);
        }
    }
    //Top-right node
    if ((y - 1 < this->oy) && (y - 1 >= 0) && (x + 1 < this->ox) && (x + 1 > 0))
    {
        if (!map[x + 1][y - 1]->itsBlock())
        {
            map[x + 1][y - 1]->setDiag(true);
            neighbours.push_back(map[x + 1][y - 1]);
        }
    }
    //Bottom-left node
    if ((y + 1 < this->oy) && (y + 1 > 0) && (x - 1 < this->ox) && (x - 1 >= 0))
    {
        if (!map[x - 1][y + 1]->itsBlock())
        {
            map[x - 1][y + 1]->setDiag(true);
            neighbours.push_back(map[x - 1][y + 1]);
        }
    }
    //Bottom-right node
    if ((y + 1 < this->oy) && (y + 1 > 0) && (x + 1 < this->ox) && (x + 1 > 0))
    {
        if (!map[x + 1][y + 1]->itsBlock())
        {
            map[x + 1][y + 1]->setDiag(true);
            neighbours.push_back(map[x + 1][y + 1]);
        }
    }
    return neighbours;
}