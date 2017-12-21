#ifndef MUSIC_H
#define MUSIC_H
#include "fmod.hpp"
#include "common.h"
#include "fmod_studio.hpp"
#include "fmod_errors.h"
class Music {

    public:
        Music();
        ~Music();
        void playSound();
        void updateSound();
        void closeSoundSystem();
    private:
        bool playing= false;
        FMOD::System *lowLevelSystem = NULL;
        FMOD::Studio::System *studioSystem = NULL;
        FMOD::Sound *sound1;
        FMOD::Channel *channel = 0;
        FMOD_RESULT result;
        unsigned int version;
        void *extradriverdata = 0;
        //EVENTS
        FMOD::Studio::EventDescription *select;
        FMOD::Studio::EventInstance *soundInstance;
        //BANKS
        FMOD::Studio::Bank *masterBank;
        FMOD::Studio::Bank *stringsBank;
        FMOD::Studio::Bank *droraniaBank;
};

#endif