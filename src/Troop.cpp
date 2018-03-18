#include "Troop.h"
#include "GraphicEngine/Model.h"
#include "GraphicEngine/SceneNode.h"
#include "MathEngine/Vector2.h"

Troop::Troop(SceneNode* scene, const wchar_t* path, i32 qnty, i32 ID){
    max = qnty;
    modelVector = std::vector< Model* >(max);
    positionVector = std::vector< Vector2<f32> >(max);
    for(i32 i = 0; i < max; i++){
        modelVector[i] = new Model(scene, ID, path);
        positionVector[i] = Vector2<f32>();
    }
}

Troop::~Troop(){
    modelVector.clear();
}

void Troop::setPosition(Vector2<f32> vectorPos){
    for(i32 i = 0; i < max; i++){
        positionVector[i] = vectorPos + i * 5.f;
    }
}
void Troop::moveTroops(Vector2<f32> vectorMov){

}