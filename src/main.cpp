#include <iostream>
#include "numero.h"
#include "3DModel.h"
#include "Animation.h"
#include "Building.h"
#include "Entity.h"
#include "Game.h"
#include "GameState.h"
#include "Graphics.h"
#include "Hud.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "Melee.h"
#include "Player.h"
#include "Ranged.h"
#include "Tower.h"
#include "Unit.h"
#include "UserInput.h"
using namespace std;


int main(){
    numero** v;
    v = new numero*[3];
    v[0] = new numero(3, "pepe");
    v[1] = new numero(4, "roman");
    v[2] = new numero(5, "jorge");

    cout << "Hello world." << endl;
    cout << "Tu suma de prueba es: " << v[0]->suma(*v[1]) << endl;
    for (int x = 0; x < 2; x++){
        cout << v[x]->getName() << endl;
    }
    delete v;
    return 0;
}