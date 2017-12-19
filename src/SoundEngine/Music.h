#ifndef MUSIC_H
#define MUSIC_H
#include "fmod.hpp"
#include "common.h"
class Music {

    public:
        Music();
        ~Music();
        void playSound();
        void updateSound();
        void closeSoundSystem();
    private:
        bool playing= false;
        FMOD::System *system;
        FMOD::Sound *sound1;
        FMOD::Channel *channel = 0;
        FMOD_RESULT result;
        unsigned int version;
        void *extradriverdata = 0;
};

#endif