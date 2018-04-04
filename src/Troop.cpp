#include "Troop.h"
#include "GraphicEngine/Model.h"
#include "GraphicEngine/SceneNode.h"
#include "MathEngine/Vector3.h"
#include "MathEngine/Vector2.h"
#include <GraphicEngine/Window.h>
#include <WorldEngine/WorldGeometry.h>

Troop::Troop(SceneNode* scene, const wchar_t* path, i32 qnty, i32 ID){
    max = qnty;
    modelVector = std::vector< Model* >(max);
    positionVector = std::vector< Vector3<f32> >(max);
    for(i32 i = 0; i < max; i++){
        modelVector[i] = new Model(scene, ID, path);
        positionVector[i] = Vector3<f32>();
        Window::Instance() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(
            modelVector[i] -> getModel() -> getMesh(), irr::video::SColor(255, 125, 125, 0)
        );
        modelVector[i]->setScale(Vector3<f32>(25,25,25));
        modelVector[i]->setActive(true);
    }
    alignmentWeight = 1.0;
    cohesionWeight = 1.0;
    separationWeight = 1.1;
}

Troop::~Troop(){
    modelVector.clear();
}

Vector2<f32> Troop::alignment(){
    Vector2<f32> dummy = Vector2<f32>();
    return dummy;
}

Vector2<f32> Troop::cohesion(){
    Vector2<f32> dummy = Vector2<f32>();
    double length = std::sqrt(std::pow(positionVector[actualIndex].x, 2) + std::pow(positionVector[actualIndex].z, 2));
    for(i32 i = 0; i < max; i++){
        if(i != actualIndex){
            dummy.x += positionVector[i].x;
            dummy.y += positionVector[i].z;
        }
    }
    dummy.x = dummy.x / max;
    dummy.y = dummy.y / max;

    dummy = Vector2<f32>(dummy.x - positionVector[actualIndex].x, dummy.y - positionVector[actualIndex].z);

    dummy.x = dummy.x / length;
    dummy.y = dummy.y / length;
    return dummy;
}

Vector2<f32> Troop::separation(){
    Vector2<f32> dummy = Vector2<f32>();
    double length = std::sqrt(std::pow(positionVector[actualIndex].x, 2) + std::pow(positionVector[actualIndex].z, 2));
    for(i32 i = 0; i < max; i++){
        if(i != actualIndex){
            dummy.x += positionVector[i].x - positionVector[actualIndex].x;
            dummy.y += positionVector[i].z - positionVector[actualIndex].z;
        }
    }
    dummy.x = (-dummy.x) / max;
    dummy.y = (-dummy.y) / max;

    dummy.x = dummy.x / length;
    dummy.y = dummy.y / length;
    return dummy;
}


Vector3<f32> Troop::calculateFlocking(){
    Vector3<f32> dummy = Vector3<f32>();
    Vector2<f32> _alignment = alignment(); 
    Vector2<f32> _cohesion = cohesion();
    Vector2<f32> _separation = separation();
    
    dummy.x = _alignment.x * alignmentWeight + _cohesion.x * cohesionWeight + _separation.x * separationWeight;
    dummy.z = _alignment.y * alignmentWeight + _cohesion.y * cohesionWeight + _separation.y * separationWeight;
    return dummy;
}

void Troop::setPosition(Vector3<f32> vectorPos){
    positionVector[0] = Vector3<f32>(vectorPos.x - 25, vectorPos.y, vectorPos.z -25);
    positionVector[1] = Vector3<f32>(vectorPos.x - 25, vectorPos.y, vectorPos.z +25);
    positionVector[2] = Vector3<f32>(vectorPos.x + 25, vectorPos.y, vectorPos.z +25);
    positionVector[3] = Vector3<f32>(vectorPos.x + 25, vectorPos.y, vectorPos.z -25);

    for(i32 i = 0; i < max; i++){
        modelVector[i]->setPosition(positionVector[i]);
    }
}
void Troop::moveTroops(Vector3<f32> vectorMov){
    //WorldGeometry::Instance()->getNeighborUnits(positionVector[0].toVector2());
    for(i32 i = 0; i < max; i++){
        actualIndex = i;
        positionVector[i] = positionVector[i] + vectorMov + calculateFlocking();
    /* Work on rotation */
        //modelVector[i]->rotate(vectorMov.x, vectorMov.z);
        modelVector[i]->setPosition(positionVector[i]);
    }
}