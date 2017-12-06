#include "troop.h"
troop::troop(int x, int y, int z, irr::scene::ISceneManager *smgrData){
    posX = x;
    posY = y;
    posZ = z;
    speed = 0.1;
    times = 0;
    mov = false;
    smgr = smgrData;
    cube = smgr->addCubeSceneNode(20.f);
    vectorDes = new irr::core::vector3df(0, 20.f, 0);
    vectorPos = new irr::core::vector3df(0, 20.f, 0);
    vectorMov = new irr::core::vector3df(0, 20.f, 0);

    if (cube)
    {
        cube->setPosition(irr::core::vector3df(x * 20.f, z * 20.f, y * 20.f));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr->getMeshManipulator()->setVertexColors(cube->getMesh(), irr::video::SColor(0, 255, 255, 255));
    }
}
troop::troop(const troop& orig0){

}
troop::~troop(){

}
int troop::getX(){
    return this->posX;
}

int troop::getY()
{
    return this->posY;
}

int troop::getZ()
{
    return this->posZ;
}
irr::scene::IMeshSceneNode* troop::getCube(){
    return this->cube;
}
void troop::moveTroop(){
    if(mov){
        if (abs(vectorDes->X - vectorPos->X) < 5.0 && abs(vectorDes->Z - vectorPos->Z) < 5.0)
        {
            mov = false;
            //vectorMov->X = 0;
            //vectorMov->Z = 0;
            //vectorDes->X = 0;
            //vectorDes->Z = 0;
        }
        else{
            *vectorPos = cube->getPosition();
            vectorPos->X += vectorMov->X;
            vectorPos->Z += vectorMov->Z;
            cube->setPosition(*vectorPos);
            std::cout << "X: " << vectorPos->X << " Y: " << vectorPos->Z << std::endl;
        }
    }
}
void troop::updateTroop(){
    moveTroop();
}
void troop::setPos(irr::core::vector3df *vectorData){
    this->vectorPos = vectorData;
}
void troop::setDes(irr::core::vector3df vectorData){

        vectorDes->X = vectorData.X;
        vectorDes->Z = vectorData.Z;

        float distance, distX, distZ;
        distX = vectorData.X - vectorPos->X;
        distZ = vectorData.Z - vectorPos->Z;
        distance = sqrt(abs(distX) + abs(distZ));

        vectorMov->X = (distX / distance) * speed;
        vectorMov->Z = (distZ / distance) * speed;

        mov = true;
}
