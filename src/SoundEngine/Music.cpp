#include "Music.h"

Music::Music() {
    Common_Init(&extradriverdata);
    //INIT STUDIO SYSTEM
    FMOD::Studio::System::create(&studioSystem);
    this->studioSystem->getLowLevelSystem(&lowLevelSystem);
    this->lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
    this->lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
    this->studioSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, &extradriverdata);
    //LOAD BANKS
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Drorania.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &droraniaBank));
    ERRCHECK(studioSystem->loadBankFile("media/soundBank/Kaonov.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &kaonovBank));
    this->pause = true;
    //EVENTS DESCRIPTIONS
    //SELECT
        //DRORANIA
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Drorania_melee_S", &_DroraniaSelectMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Drorania_melee_A", &_DroraniaSelectMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Drorania_ranged_S", &_DroraniaSelectRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Drorania_ranged_A", &_DroraniaSelectRangedA));

        ERRCHECK(_DroraniaSelectMeleeS->createInstance(&DroraniaSelectMeleeS));
        ERRCHECK(_DroraniaSelectMeleeA->createInstance(&DroraniaSelectMeleeA));
        ERRCHECK(_DroraniaSelectRangedS->createInstance(&DroraniaSelectRangedS));
        ERRCHECK(_DroraniaSelectRangedA->createInstance(&DroraniaSelectRangedA));
        //KAONOV
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Kaonov_melee_S", &_KaonovSelectMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Kaonov_melee_A", &_KaonovSelectMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Kaonov_ranged_S", &_KaonovSelectRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitSelect/Kaonov_ranged_A", &_KaonovSelectRangedA));

        ERRCHECK(_KaonovSelectMeleeS->createInstance(&KaonovSelectMeleeS));
        ERRCHECK(_KaonovSelectMeleeA->createInstance(&KaonovSelectMeleeA));
        ERRCHECK(_KaonovSelectRangedS->createInstance(&KaonovSelectRangedS));
        ERRCHECK(_KaonovSelectRangedA->createInstance(&KaonovSelectRangedA));
    //MOVEMENT
        //DRORANIA
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Drorania_melee_S", &_DroraniaMovementMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Drorania_melee_A", &_DroraniaMovementMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Drorania_ranged_S", &_DroraniaMovementRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Drorania_ranged_A", &_DroraniaMovementRangedA));

        ERRCHECK(_DroraniaMovementMeleeS->createInstance(&DroraniaMovementMeleeS));
        ERRCHECK(_DroraniaMovementMeleeA->createInstance(&DroraniaMovementMeleeA));
        ERRCHECK(_DroraniaMovementRangedS->createInstance(&DroraniaMovementRangedS));
        ERRCHECK(_DroraniaMovementRangedA->createInstance(&DroraniaMovementRangedA));
        //KAONOV
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Kaonov_melee_S", &_KaonovMovementMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Kaonov_melee_A", &_KaonovMovementMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Kaonov_ranged_S", &_KaonovMovementRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Kaonov_ranged_A", &_KaonovMovementRangedA));

        ERRCHECK(_KaonovMovementMeleeS->createInstance(&KaonovMovementMeleeS));
        ERRCHECK(_KaonovMovementMeleeA->createInstance(&KaonovMovementMeleeA));
        ERRCHECK(_KaonovMovementRangedS->createInstance(&KaonovMovementRangedS));
        ERRCHECK(_KaonovMovementRangedA->createInstance(&KaonovMovementRangedA));
    //ATTACK
        //DRORANIA
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Drorania_melee_S", &_DroraniaAttackMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Drorania_melee_A", &_DroraniaAttackMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Drorania_ranged_S", &_DroraniaAttackRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Drorania_ranged_A", &_DroraniaAttackRangedA));

        ERRCHECK(_DroraniaAttackMeleeS->createInstance(&DroraniaAttackMeleeS));
        ERRCHECK(_DroraniaAttackMeleeA->createInstance(&DroraniaAttackMeleeA));
        ERRCHECK(_DroraniaAttackRangedS->createInstance(&DroraniaAttackRangedS));
        ERRCHECK(_DroraniaAttackRangedA->createInstance(&DroraniaAttackRangedA));
        //KAONOV
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Kaonov_melee_S", &_KaonovAttackMeleeS));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Kaonov_melee_A", &_KaonovAttackMeleeA));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Kaonov_ranged_S", &_KaonovAttackRangedS));
        ERRCHECK(studioSystem->getEvent("event:/UnitAttack/Kaonov_ranged_A", &_KaonovAttackRangedA));

        ERRCHECK(_KaonovAttackMeleeS->createInstance(&KaonovAttackMeleeS));
        ERRCHECK(_KaonovAttackMeleeA->createInstance(&KaonovAttackMeleeA));
        ERRCHECK(_KaonovAttackRangedS->createInstance(&KaonovAttackRangedS));
        ERRCHECK(_KaonovAttackRangedA->createInstance(&KaonovAttackRangedA));

    //MUSIC
        ERRCHECK(studioSystem->getEvent("event:/Music/DroraniaMusic", &_DroraniaMusic));
        ERRCHECK(_DroraniaMusic->createInstance(&DroraniaMusic));
    //MAP SOUND
    soundEvent["UnitMovementDroraniaMeleeS"] = DroraniaMovementMeleeS;
    soundEvent["UnitMovementDroraniaMeleeA"] = DroraniaMovementMeleeA;
    soundEvent["UnitMovementDroraniaRangedS"] = DroraniaMovementRangedS;
    soundEvent["UnitMovementDroraniaRangedA"] = DroraniaMovementRangedA;
    soundEvent["UnitMovementKaonovMeleeS"] = KaonovMovementMeleeS;
    soundEvent["UnitMovementKaonovMeleeA"] = KaonovMovementMeleeA;
    soundEvent["UnitMovementKaonovRangedS"] = KaonovMovementRangedS;
    soundEvent["UnitMovementKaonovRangedA"] = KaonovMovementRangedA;
    soundEvent["UnitAttackDroraniaMeleeS"] = DroraniaAttackMeleeS;
    soundEvent["UnitAttackDroraniaMeleeA"] = DroraniaAttackMeleeA;
    soundEvent["UnitAttackDroraniaRangedS"] = DroraniaAttackRangedS;
    soundEvent["UnitAttackDroraniaRangedA"] = DroraniaAttackRangedA;
    soundEvent["UnitAttackKaonovMeleeS"] = KaonovAttackMeleeS;
    soundEvent["UnitAttackKaonovMeleeA"] = KaonovAttackMeleeA;
    soundEvent["UnitAttackKaonovRangedS"] = KaonovAttackRangedS;
    soundEvent["UnitAttackKaonovRangedA"] = KaonovAttackRangedA;
    soundEvent["UnitSelectDroraniaMeleeS"] = DroraniaSelectMeleeS;
    soundEvent["UnitSelectDroraniaMeleeA"] = DroraniaSelectMeleeA;
    soundEvent["UnitSelectDroraniaRangedS"] = DroraniaSelectRangedS;
    soundEvent["UnitSelectDroraniaRangedA"] = DroraniaSelectRangedA;
    soundEvent["UnitSelectKaonovMeleeS"] = KaonovSelectMeleeS;
    soundEvent["UnitSelectKaonovMeleeA"] = KaonovSelectMeleeA;
    soundEvent["UnitSelectKaonovRangedS"] = KaonovSelectRangedS;
    soundEvent["UnitSelectKaonovRangedA"] = KaonovSelectRangedA;

    soundEvent["DroraniaMusic"] = DroraniaMusic;
    //result = studioSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
    //result = studioSystem->createSound(Common_MediaPath("../media/drumloop.wav"), FMOD_DEFAULT, 0, &sound1);
    //result = sound1->setMode(FMOD_LOOP_OFF);
    //EVENTS
    //ERRCHECK(studioSystem->getEvent("event:/UnitMovement/Drorania_melee_S", &select));
    //select->loadSampleData();
    //selec->createInstance(&soundInstance);
}

Music::~Music() {
    this->closeSoundSystem();
    delete studioSystem;
    delete lowLevelSystem;
}
void Music::playVoice(string voiceData){
    if(!pause){
        voiceInstance->getPlaybackState(&voicePlayBackState);
        if (voicePlayBackState != FMOD_STUDIO_PLAYBACK_PLAYING)
        {
            if(rand() % 100 < 50){
                const char *c = voiceData.c_str();
                voiceInstance = soundEvent.find(c)->second;
                ERRCHECK(voiceInstance->start());
                ERRCHECK(voiceInstance->release());
            }
        }
    }
}
void Music::playMusic(string musicData){
    if (!pause)
    {
        musicInstance->getPlaybackState(&musicPlayBackState);
        if (musicPlayBackState != FMOD_STUDIO_PLAYBACK_PLAYING)
        {
            if(!musicPlaying){
                const char *c = musicData.c_str();
                musicInstance = soundEvent.find(c)->second;
                musicPlaying = true;
            }
            ERRCHECK(musicInstance->start());
            ERRCHECK(musicInstance->release());
        }
    }
}
void Music::playSFX(string sfxData){
    if (!pause)
    {
        //NOT IMPLEMENTED
        //sfxInstance->getPlaybackState(&playBackState);
        //if (playBackState != FMOD_STUDIO_PLAYBACK_PLAYING)
        //{
            //const char *c = sfxData.c_str();
            //sfxInstance = soundEvent.find(c)->second;
            //ERRCHECK(sfxInstance->start());
            //ERRCHECK(sfxInstance->release());
        //}
    }
}
void Music::updateSound(){
    if(!pause){
        Common_Update();
        this->studioSystem->update();
    }
}
void Music::closeSoundSystem(){
    this->masterBank->unload();
    this->stringsBank->unload();
    this->kaonovBank->unload();
    this->droraniaBank->unload();
    this->lowLevelSystem->release();
    this->studioSystem->unloadAll();
    this->studioSystem->release();
    Common_Close();
}
void Music::setMusicVolume(float musicVolume){
    this->musicInstance->setVolume(musicVolume);
}
void Music::setVoiceVolume(float voiceVolume){
    this->voiceInstance->setVolume(voiceVolume);
}
void Music::setSfxVolumne(float sfxVolume){
    this->sfxInstance->setVolume(sfxVolume);
}
void setListenerPosition(Vector3<float> posData){
    //NOT IMPLEMENTED YET
}
void Music::setPause(bool pauseData){
    this->pause = pauseData;
}
void Music::stopAll(){
    this->voiceInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    this->sfxInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    this->musicInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    this->pause = true;
    this->musicPlaying = false;
}
bool Music::getMusicPlaying(){

}