#include "Entity.h"

#include "Game.h"

//ToDo: temp
Entity::Entity(SceneNode *layer, int id, int size) {
    this->ID = id;
    this->target = NULL;
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
    model = new Model(layer, id, size);
    hitbox = new Box3D<float>();
    position = new Vector3<float>();

    this -> tookDamageTimer = 0.1;
}

Entity::Entity(SceneNode *layer, int id, const wchar_t *path) {
    this->ID = id;
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
    model = new Model(layer, id, path);
    hitbox = new Box3D<float>();
    position = new Vector3<float>();
}

Entity::~Entity() {
    delete position;
    delete hitbox;
    delete model;
    
    if (target != NULL) delete target;
}

int Entity::getHP() {
    return hp;
}

/*
* Decreases Hp
* dmg = quantity of hp to drecrease
*/
void Entity::takeDamage(int dmg) {
    //std::cout << "I take " << dmg << " damage. I still have " << hp << " health." << std::endl;
    hp = hp-dmg;
    // Tint the model red
    tookDamageCountdown = tookDamageTimer;
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(255, 255, 0, 0));
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Entity::die() {
    //std::cout << "I die" << std::endl;
    //ToDo: DEJAR DE DIBUJAR CUBOS
    // SOLO SE MANDAN AL 0,0,0
    //
    //
    //
    
    this -> setPosition(Vector3<float>(0, 0, 0));
    //delete this; 
}

void Entity::changeRedTint() {
    if (!finished && tookDamageCountdown <= 0) {
        Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), baseColor);
    } else {
        tookDamageCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
}

void Entity::setPosition(Vector3<float> vectorData){
    this->position->set(vectorData);
    this->model->setPosition(vectorData);
    this->hitbox->set(model -> getModel() -> getTransformedBoundingBox());
}

Vector3<float>* Entity::getPosition() {
    return position;
}

Box3D<float>* Entity::getHitbox() {
    return hitbox;
}

Model* Entity::getModel() {
    return model;
}

Enumeration::Team Entity::getTeam() {
    return team;
}

void Entity::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he cant attack anything
    target = newTarget;
}

int Entity::getAttackRange() {
    return attackRange;
}

int Entity::getViewRadius() {
    return viewRadius;
}