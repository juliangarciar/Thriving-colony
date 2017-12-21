#include "Music.h"

Music::Music() {
    Common_Init(&extradriverdata);
    //result = FMOD::System_Create(&system);
    //result = system->getVersion(&version);
    //INIT STUDIO SYSTEM
    FMOD::Studio::System::create(&studioSystem);
    this->studioSystem->getLowLevelSystem(&lowLevelSystem);
    this->lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
    this->lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
    this->studioSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, &extradriverdata);
    //LOAD BANKS
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Drorania_melee_S.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &droraniaBank));

    //result = studioSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
    //result = studioSystem->createSound(Common_MediaPath("../media/drumloop.wav"), FMOD_DEFAULT, 0, &sound1);
    result = sound1->setMode(FMOD_LOOP_OFF);
    //EVENTS
    ERRCHECK(studioSystem->getEvent("event:/Drorania_melee_S_mov_1", &select));
    select->loadSampleData();
    //selec->createInstance(&soundInstance);
}

Music::~Music() {
    this->closeSoundSystem();
    delete studioSystem;
    delete lowLevelSystem;
    delete sound1;
    delete channel;
}
void Music::playSound(){
    ERRCHECK(select->createInstance(&soundInstance));
    ERRCHECK(soundInstance->start());
    playing = true;
    //soundInstance->release();
    //playing = false;
    //result = system->playSound(sound1, 0, false, &channel);
}
void Music::updateSound(){
    Common_Update();
    //result = channel->isPlaying(&playing);
    //if(!playing){
    if(!playing){
        playSound();
    }
        
        
    //}
    result = studioSystem->update();
}
void Music::closeSoundSystem(){
    //result = sound1->release();
    //result = lowLevelSystem->close();
    //result = lowLevelSystem->release();
    //result = studioSystem->close();
    this->masterBank->unload();
    this->stringsBank->unload();
    this->droraniaBank->unload();
    result = studioSystem->release();
    Common_Close();
}