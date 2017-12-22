#ifndef MUSIC_H
#define MUSIC_H
#include "fmod.hpp"
#include "common.h"
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include "../Enumeration.h"
#include "../GraphicEngine/Vector3.h"
#include <map>
#include <string>

using namespace std;
class Music {

    public:
        Music();
        ~Music();
        void playVoice(string voiceData);
        void playMusic(string musicData);
        void playSFX(string sfxData);
        void updateSound();
        void closeSoundSystem();
        void setMusicVolume(float musicVolume);
        void setVoiceVolume(float voiceVolume);
        void setSfxVolumne(float sfxVolume);
        void setListenerPosition(Vector3<float> posData);
        void setPause(bool pauseData);
        void stopAll();
        bool getMusicPlaying();
    private:
    //NUEVO
      //map<string, FMOD::Studio::Bank *> banks;
      //map<string, FMOD::Studio::EventDescription *> eventDescriptions;
      map<string, FMOD::Studio::EventInstance*> soundEvent;
      //
      bool musicPlaying = false;
      bool pause = false;
      FMOD::System *lowLevelSystem = NULL;
      FMOD::Studio::System *studioSystem = NULL;
      void *extradriverdata = 0;
    //EVENTS DESCIPTIONS
    //SELECT
        //DRORANIA
        FMOD::Studio::EventDescription *_DroraniaSelectMeleeS;
        FMOD::Studio::EventDescription *_DroraniaSelectMeleeA;
        FMOD::Studio::EventDescription *_DroraniaSelectRangedS;
        FMOD::Studio::EventDescription *_DroraniaSelectRangedA;
        //KAONOV
        FMOD::Studio::EventDescription *_KaonovSelectMeleeS;
        FMOD::Studio::EventDescription *_KaonovSelectMeleeA;
        FMOD::Studio::EventDescription *_KaonovSelectRangedS;
        FMOD::Studio::EventDescription *_KaonovSelectRangedA;
    //MOVEMENT
        //DRORANIA
        FMOD::Studio::EventDescription *_DroraniaMovementMeleeS;
        FMOD::Studio::EventDescription *_DroraniaMovementMeleeA;
        FMOD::Studio::EventDescription *_DroraniaMovementRangedS;
        FMOD::Studio::EventDescription *_DroraniaMovementRangedA;
        //KAONOV
        FMOD::Studio::EventDescription *_KaonovMovementMeleeS;
        FMOD::Studio::EventDescription *_KaonovMovementMeleeA;
        FMOD::Studio::EventDescription *_KaonovMovementRangedS;
        FMOD::Studio::EventDescription *_KaonovMovementRangedA;
    //ATTACK
        //DRORANIA
        FMOD::Studio::EventDescription *_DroraniaAttackMeleeS;
        FMOD::Studio::EventDescription *_DroraniaAttackMeleeA;
        FMOD::Studio::EventDescription *_DroraniaAttackRangedS;
        FMOD::Studio::EventDescription *_DroraniaAttackRangedA;
        //KAONOV
        FMOD::Studio::EventDescription *_KaonovAttackMeleeS;
        FMOD::Studio::EventDescription *_KaonovAttackMeleeA;
        FMOD::Studio::EventDescription *_KaonovAttackRangedS;
        FMOD::Studio::EventDescription *_KaonovAttackRangedA;
    //MUSIC
        FMOD::Studio::EventDescription *_DroraniaMusic;
    //EVENTS INSTANCE
    //SELECT
        //DRORANIA
        FMOD::Studio::EventInstance *DroraniaSelectMeleeS;
        FMOD::Studio::EventInstance *DroraniaSelectMeleeA;
        FMOD::Studio::EventInstance *DroraniaSelectRangedS;
        FMOD::Studio::EventInstance *DroraniaSelectRangedA;
        //KAONOV
        FMOD::Studio::EventInstance *KaonovSelectMeleeS;
        FMOD::Studio::EventInstance *KaonovSelectMeleeA;
        FMOD::Studio::EventInstance *KaonovSelectRangedS;
        FMOD::Studio::EventInstance *KaonovSelectRangedA;
    //MOVEMENT
        //DRORANIA
        FMOD::Studio::EventInstance *DroraniaMovementMeleeS;
        FMOD::Studio::EventInstance *DroraniaMovementMeleeA;
        FMOD::Studio::EventInstance *DroraniaMovementRangedS;
        FMOD::Studio::EventInstance *DroraniaMovementRangedA;
        //KAONOV
        FMOD::Studio::EventInstance *KaonovMovementMeleeS;
        FMOD::Studio::EventInstance *KaonovMovementMeleeA;
        FMOD::Studio::EventInstance *KaonovMovementRangedS;
        FMOD::Studio::EventInstance *KaonovMovementRangedA;
    //ATTACK
        //DRORANIA
        FMOD::Studio::EventInstance *DroraniaAttackMeleeS;
        FMOD::Studio::EventInstance *DroraniaAttackMeleeA;
        FMOD::Studio::EventInstance *DroraniaAttackRangedS;
        FMOD::Studio::EventInstance *DroraniaAttackRangedA;
        //KAONOV
        FMOD::Studio::EventInstance *KaonovAttackMeleeS;
        FMOD::Studio::EventInstance *KaonovAttackMeleeA;
        FMOD::Studio::EventInstance *KaonovAttackRangedS;
        FMOD::Studio::EventInstance *KaonovAttackRangedA;
    //MUSIC
        FMOD::Studio::EventInstance *DroraniaMusic;
    //BANKS
        FMOD::Studio::Bank *masterBank;
        FMOD::Studio::Bank *stringsBank;
        FMOD::Studio::Bank *droraniaBank;
        FMOD::Studio::Bank *kaonovBank;
    //CHECKS
        FMOD_STUDIO_PLAYBACK_STATE voicePlayBackState;
        FMOD_STUDIO_PLAYBACK_STATE musicPlayBackState;
    //INSTANCE TYPES
        FMOD::Studio::EventInstance *voiceInstance = NULL;
        FMOD::Studio::EventInstance *musicInstance = NULL;
        FMOD::Studio::EventInstance *sfxInstance = NULL;
};
#endif