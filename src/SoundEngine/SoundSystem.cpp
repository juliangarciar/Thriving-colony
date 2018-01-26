#include "SoundSystem.h"
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line) {
	if (result != FMOD_OK) {
		std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
		exit(-1);

	}
}

SoundSystem* SoundSystem::pinstance = 0;

SoundSystem* SoundSystem::Instance() {
    if(pinstance == 0) {
        pinstance = new SoundSystem();
    }
    return pinstance;
}

SoundSystem::SoundSystem() {
    paused = false;
    ERRCHECK(FMOD_Studio_System_Create(&system, FMOD_VERSION));
    ERRCHECK(FMOD_Studio_System_GetLowLevelSystem(system, &lowLevelSystem));
    
    ERRCHECK(FMOD_System_SetSoftwareFormat(lowLevelSystem, 0, FMOD_SPEAKERMODE_STEREO, 0));
    ERRCHECK(FMOD_System_SetOutput(lowLevelSystem, FMOD_OUTPUTTYPE_AUTODETECT));
    //INITIALIZE SYSTEM
    ERRCHECK(FMOD_Studio_System_Initialize(system, 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
    //LOAD BANKS
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, "./media/soundBank/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, "./media/soundBank/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, "./media/soundBank/Drorania.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &droraniaBank));
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, "./media/soundBank/Kaonov.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &kaonovBank));
    banks["masterBank"] = masterBank;
	banks["stringsBank"] = stringsBank;
	banks["droraniaBank"] = droraniaBank;
	banks["kaonovBank"] = kaonovBank;

    //GETTING BUSMASTER ID (NOT WORKING)
    //ERRCHECK(FMOD_Studio_System_LookupID(system, , &systemID));
    //ERRCHECK(FMOD_Studio_System_GetBus(system, systemID, &bus));
}

SoundSystem::~SoundSystem() {
    banks.clear();
    eventDescriptions.clear();
    soundEvents.clear();
    FMOD_Studio_Bank_Unload(droraniaBank);
    FMOD_Studio_Bank_Unload(kaonovBank);
    FMOD_Studio_Bank_Unload(stringsBank);
    FMOD_Studio_Bank_Unload(masterBank);

    FMOD_Studio_System_UnloadAll(system);
    FMOD_Studio_System_Release(system);
}

//LOAD DESCRIPTIONS AND EVENTS
void SoundSystem::initSystem() {
    string c;
    c = "event:/Music/DroraniaMusic";
    createEvent(c);
    c = "event:/UnitSelect/Drorania_melee_S";       
    createEvent(c);
    c = "event:/UnitSelect/Drorania_melee_A";
    createEvent(c);
    c = "event:/UnitSelect/Drorania_ranged_S";
    createEvent(c);
    c = "event:/UnitSelect/Drorania_ranged_A";
    createEvent(c);
    c = "event:/UnitSelect/Kaonov_melee_S";
    createEvent(c);
    c = "event:/UnitSelect/Kaonov_melee_S";
    createEvent(c);
    c = "event:/UnitSelect/Kaonov_melee_A";
    createEvent(c);
    c = "event:/UnitSelect/Kaonov_ranged_S";
    createEvent(c);
    c = "event:/UnitSelect/Kaonov_ranged_A";
    createEvent(c);
    c = "event:/UnitMovement/Drorania_melee_S";
    createEvent(c);
    c = "event:/UnitMovement/Drorania_melee_A";
    createEvent(c);
    c = "event:/UnitMovement/Drorania_ranged_S";
    createEvent(c);
    c = "event:/UnitMovement/Drorania_ranged_A";
    createEvent(c);
    c = "event:/UnitMovement/Kaonov_melee_S";
    createEvent(c);
    c = "event:/UnitMovement/Kaonov_melee_A";
    createEvent(c);
    c = "event:/UnitMovement/Kaonov_ranged_S";
    createEvent(c);
    c = "event:/UnitMovement/Kaonov_ranged_A";
    createEvent(c);
    c = "event:/UnitAttack/Drorania_melee_S";
    createEvent(c);
    c = "event:/UnitAttack/Drorania_melee_A";
    createEvent(c);
    c = "event:/UnitAttack/Drorania_ranged_S";
    createEvent(c);
    c = "event:/UnitAttack/Drorania_ranged_A";
    createEvent(c);
    c = "event:/UnitAttack/Kaonov_melee_S";
    createEvent(c);
    c = "event:/UnitAttack/Kaonov_melee_A";
    createEvent(c);
    c = "event:/UnitAttack/Kaonov_ranged_S";
    createEvent(c);
    c = "event:/UnitAttack/Kaonov_ranged_A";
    createEvent(c);
}

FMOD_STUDIO_EVENTINSTANCE* SoundSystem::getEvent(string pathData) {
    const char *c = pathData.c_str();
    return soundEvents.find(c) -> second;

}

void SoundSystem::setVolume(float volData) {
   //ERRCHECK(FMOD_Studio_Bus_SetVolume(bus, volData));
}

//NOT IMPLEMENTED
void SoundSystem::setListernerPosition(Vector3<float> vectorData) {

}

void SoundSystem::update() {
    if(!paused)
        ERRCHECK(FMOD_Studio_System_Update(system));
}

void SoundSystem::setStat(bool data) {
    this -> paused = data;
}

/*
    BASED ON JESUS SOUND SYSTEM
    MODIFIED BY JULIAN
    EVERYTHING BASED ON soundEvent DOESN'T WORK, IS NOT NEEDED
    IT WILL BE DELETED SOON
*/

FMOD_STUDIO_EVENTDESCRIPTION* SoundSystem::createDescription(const char* path, FMOD_STUDIO_EVENTDESCRIPTION* desc) {
	ERRCHECK(FMOD_Studio_System_GetEvent(system, path, &desc));	        //Create the event
	eventDescriptions[path] = desc;				                    //Add the descriptions to the event descriptions map
	return desc;
}

void SoundSystem::createEvent(std::string eventPath) {
	FMOD_STUDIO_EVENTDESCRIPTION * eventDesc = NULL;					//Initialize the event description
	FMOD_STUDIO_EVENTINSTANCE * eventInst    = NULL;					//Initialize the event instance
	//SoundEvent * newEvent					 = NULL; 					//Initialize the event
	
	//Search the description to know if it's already created
	if (eventDescriptions[eventPath] != NULL) 
		eventDesc = eventDescriptions[eventPath];					 //Set it to the eventDesc var
	else {
		eventDesc = createDescription(eventPath.c_str(), eventDesc); //Else set a new event description
		eventDescriptions[eventPath] = eventDesc;					 //And store it at the descriptions map
	}

	ERRCHECK(FMOD_Studio_EventDescription_CreateInstance(eventDesc, &eventInst));				//Set the event instance
    
	soundEvents[eventPath] = eventInst;
}

//Used for events without position as the events from the menu
void SoundSystem::playEvent(SoundEvent* event) {
	event -> start();					
}

void SoundSystem::playMusicEvent(string c) {
    if(musicPlay) {
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(musicInstance, &state));
        if(state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            musicInstance = soundEvents.find(c) -> second;
            ERRCHECK(FMOD_Studio_EventInstance_Start(musicInstance));
        }
    }
    else{
        FMOD_STUDIO_EVENTINSTANCE * instance;
        instance = soundEvents.find(c) -> second;
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(instance, &state));
        if(state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(instance));   
            musicInstance = instance;
            musicPlay = true;
        }
    }
}

void SoundSystem::playVoiceEvent(string c) {
    if(voicePlay) {
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(voiceInstance, &state));
        if(state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            voiceInstance = soundEvents.find(c) -> second;
            ERRCHECK(FMOD_Studio_EventInstance_Start(voiceInstance));
        }
    }
    else{
        FMOD_STUDIO_EVENTINSTANCE * instance;
        instance = soundEvents.find(c) -> second;
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(instance, &state));
        if(state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(instance));  
            voiceInstance = instance;
            voicePlay = true; 
        }
    }
}

/******************************************************
 * @brief Stops an event that is being played
 * @param eventPath path of the event to stop
 ******************************************************/
void SoundSystem::stopEvent(SoundEvent* event) {
    event -> stop();
}

/******************************************************
 * @brief Stops an event if it's being played
 * @param eventPath path of the event to stop
 ******************************************************/
void SoundSystem::checkAndStopEvent(SoundEvent* event) {
    if (event -> isPlaying()) event -> stop();
}

/*
SOUND EVENT -> THIS IS GOING TO DISSAPEAR SOON
*/
SoundEvent::SoundEvent() {}
SoundEvent::~SoundEvent() {}

void SoundEvent::start() {
    ERRCHECK(FMOD_Studio_EventInstance_Start(soundInstance));
}

void SoundEvent::stop() {
    ERRCHECK(FMOD_Studio_EventInstance_Stop(soundInstance, FMOD_STUDIO_STOP_IMMEDIATE));
}

void SoundEvent::pause() {
    FMOD_BOOL paused = false;
    FMOD_Studio_EventInstance_GetPaused(soundInstance, &paused);
    ERRCHECK(FMOD_Studio_EventInstance_SetPaused(soundInstance, !paused));
}

void SoundEvent::setVolume(float volumeData) {
    ERRCHECK(FMOD_Studio_EventInstance_SetVolume(soundInstance, volumeData));
}

void SoundEvent::setGain(float gainData) {
    ERRCHECK(FMOD_Studio_EventInstance_SetPitch(soundInstance, gainData));
}

//NOT IMPLEMENTED
void SoundEvent::setPosition(Vector3<float> vectorData) {

}

bool SoundEvent::isPlaying() {
    bool playing = false;
    FMOD_STUDIO_PLAYBACK_STATE state;
    ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(soundInstance, &state));
    if(state == 0) {
        playing = true;
    }
    return playing;
}

void SoundEvent::release() {
    ERRCHECK(FMOD_Studio_EventInstance_Release(soundInstance));
}

void SoundEvent::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *EventInstance) {
    soundInstance = EventInstance;
}

FMOD_STUDIO_EVENTINSTANCE* SoundEvent::getInstance() {
    return soundInstance;
}