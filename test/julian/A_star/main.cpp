#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "node.h"

using namespace std;
//TYPE NEEDED FOR PRIORITY QUEUE
struct comparePriority{
    bool operator()(node* const & p1, node* const & p2 ){
        return p1 -> getPriority() >= p2 -> getPriority();
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
        if(!mapData[x - 1][y] -> itsBlock() )
        neighbours.push_back(mapData[x - 1][y]);
    }
    if((y - 1) >= 0){
        if(!mapData[x][y - 1] -> itsBlock() )
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
    //INIT NEIGHBOURS DATA
    std::vector < node* > neighbors;
    //INIT MAP DATA
    node*** mapita = new node**[25];
    for (i32 x = 0; x < 25; x++)
    {
        mapita[x] = new node*[25];
        for (i32 y = 0; y < 25; y++)
        {
            mapita[x][y] = new node(x, y);
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

        start -> swapColor(sf::Color::Blue);
        end -> swapColor(sf::Color::Red);

    //DRAW OBSTACLES
    for (i32 x = 13, y = 15; x < 20; x++, y--)
    {
        mapita[x][y] -> swapColor(sf::Color::Black);
        mapita[x][y] -> setBlock(true);
    }
    //START FRONTIER
    node *current;
    frontier.push(start);

    //INIT WINDOW
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    //MAIN BUCLE
    while (window.isOpen() && !finish)
    {
        //sf::Event event;
        //while (window.pollEvent(event))
        //{
        //    if (event.type == sf::Event::Closed)
        //        window.close();
        //    
        //    
        //}
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            //Start algorithm
            if (!frontier.empty() && !finish)
            {
                
                current = frontier.top();
                //frontier.top() -> setVisited(true);
                frontier.pop();
                //SHOW PATH
                if (current == end)
                {
                    cout << "Sansacabao" << endl;
                    finish = true;
                    end -> swapColor(sf::Color::Red);

                    while (current != start)
                    {
                        current = current -> getCameFrom();
                        current -> swapColor(sf::Color::Red);
                    }
                    for (i32 x = 0; x < 25; x++)
                    {
                        for (i32 y = 0; y < 25; y++)
                        {
                            window.draw(*mapita[x][y] -> getRectangle());
                        }
                    }
                    window.display();
                    cin >> insertKey;
                }

                neighbors = getNeighbours(current, mapita);
                for (i32 i = 0; i < neighbors.size(); i++)
                {
                    newCost = current -> getWeight() + 1;
                    if (!frontier.top() -> itsCounted() || newCost < neighbors[i] -> getWeight())
                    {
                        neighbors[i] -> swapColor(sf::Color::Magenta);
                        neighbors[i] -> setWeight(newCost);
                        neighbors[i] -> setCounted(true);
                        priority = newCost + checkDistance(end, neighbors[i]);
                        neighbors[i] -> setPriority(priority);
                        neighbors[i] -> setCameFrom(current);
                        frontier.push(neighbors[i]);
                        
                    }
                }
                
                neighbors.clear();
            }
        }
        window.clear();
        
        for (i32 x = 0; x < 25; x++)
        {
            for (i32 y = 0; y < 25; y++)
            {
                window.draw(*mapita[x][y] -> getRectangle());
            }
        }
        window.display();
    }
    
    while(!frontier.empty())
        frontier.pop();
    //neighbors.clear();
    
    delete start;
    delete end;
    delete current;

    for (i32 i = 0 ; i < 24; i++)
    {
        for (i32 j = 0; j < 24; j++){
            delete mapita[i][j];
        }
        delete[] mapita[i];
    }

    delete[] mapita;
    return 0;
}