#include <iostream>
#include "Player.h"
#include "IA/IA.h"
#include "IA/VeryHappyTree.h"

using namespace std;


int main(){
    IA* pl = new IA();
    
    VeryHappyTree* t = new VeryHappyTree(pl);

    while(true) {
            t  -> makeChoice();


    }
    return 0;
}