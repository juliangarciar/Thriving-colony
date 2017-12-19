#include "Music.h"

Music::Music() {
    Common_Init(&extradriverdata);
    result = FMOD::System_Create(&system);
    result = system->getVersion(&version);
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    result = system->createSound(Common_MediaPath("../media/drumloop.wav"), FMOD_DEFAULT, 0, &sound1);
    result = sound1->setMode(FMOD_LOOP_OFF);
}

Music::~Music() {
    this->closeSoundSystem();
    delete system;
    delete sound1;
    delete channel;
}
void Music::playSound(){
    result = system->playSound(sound1, 0, false, &channel);
}
void Music::updateSound(){
    Common_Update();
    result = channel->isPlaying(&playing);
    if(!playing){
        playSound();
        
    }
    result = system->update();
}
void Music::closeSoundSystem(){
    result = sound1->release();
    result = system->close();
    result = system->release();
    Common_Close();
}