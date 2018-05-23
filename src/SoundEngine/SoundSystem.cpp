#include "SoundSystem.h"
#include <OBDEngine/ResourceManager/ResourceJSON.h>
#include <IOEngine/IO.h>

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

void ERRCHECK_fn(FMOD_RESULT result, const char *file, i32 line) {
	if (result != FMOD_OK) {
		std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
		exit(-1);

	}
}

SoundSystem* SoundSystem::pinstance = 0;

SoundSystem* SoundSystem::Instance() {
    if (pinstance == 0) {
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
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/gameConfig/AudioData/AudioConfig.json", true);

    json j = *r -> getJSON();

    for (auto& element : j["AudioBanks"]){
        FMOD_STUDIO_BANK* tmpBank = 0;
        ERRCHECK(FMOD_Studio_System_LoadBankFile(system, element["BankPath"].get<std::string>().c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &tmpBank));
        banks[element["Name"].get<std::string>()] = tmpBank;
    }
    for (auto& element1 : j["AudioConfig"]) {
        createEvent(element1["Name"].get<std::string>(), element1["EventPath"].get<std::string>());
    }

    //GETTING BUSMASTER ID (NOT WORKING)
    //ERRCHECK(FMOD_Studio_System_LookupID(system, , &systemID));
    //ERRCHECK(FMOD_Studio_System_GetBus(system, systemID, &bus));
}

SoundSystem::~SoundSystem() {
    
    eventDescriptions.clear();
    soundEvents.clear();
    for(map<string, FMOD_STUDIO_BANK*>::iterator it = banks.begin(); it != banks.end(); it++){
        FMOD_Studio_Bank_Unload(it->second);
    }
    /*FMOD_Studio_Bank_Unload(droraniaBank);
    FMOD_Studio_Bank_Unload(kaonovBank);
    FMOD_Studio_Bank_Unload(stringsBank);
    FMOD_Studio_Bank_Unload(masterBank);*/
    banks.clear();
    FMOD_Studio_System_UnloadAll(system);
    FMOD_Studio_System_Release(system);
}

FMOD_STUDIO_EVENTINSTANCE* SoundSystem::getEvent(string pathData) {
    const char *c = pathData.c_str();
    return soundEvents.find(c) -> second;

}

void SoundSystem::setVolume(f32 volData) {
   //ERRCHECK(FMOD_Studio_Bus_SetVolume(bus, volData));
}

//NOT IMPLEMENTED
void SoundSystem::setListernerPosition(Vector3<f32> vectorData) {

}

void SoundSystem::update() {
    if (!paused){
        ERRCHECK(FMOD_Studio_System_Update(system));
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(musicInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(musicInstance));   
            if(!musicPlay)
                musicPlay = true;
        }
    }    
}

void SoundSystem::setStat(bool data) {
    paused = data;
}

FMOD_STUDIO_EVENTDESCRIPTION* SoundSystem::createDescription(const char* path, FMOD_STUDIO_EVENTDESCRIPTION* desc) {
	ERRCHECK(FMOD_Studio_System_GetEvent(system, path, &desc));
	eventDescriptions[path] = desc;				                   
	return desc;
}

void SoundSystem::createEvent(std::string eventName, std::string eventPath) {
	std::cout << eventPath << "\n";
    FMOD_STUDIO_EVENTDESCRIPTION * eventDesc = nullptr;					//Initialize the event description
	FMOD_STUDIO_EVENTINSTANCE * eventInst    = nullptr;					//Initialize the event instance
	//SoundEvent * newEvent					 = nullptr; 					//Initialize the event
	
	//Search the description to know if it's already created
	if (eventDescriptions[eventName] != nullptr) 
		eventDesc = eventDescriptions[eventPath];					 //Set it to the eventDesc var
	else {
		eventDesc = createDescription(eventPath.c_str(), eventDesc); //Else set a new event description
		eventDescriptions[eventName] = eventDesc;					 //And store it at the descriptions map
	}

	ERRCHECK(FMOD_Studio_EventDescription_CreateInstance(eventDesc, &eventInst));				//Set the event instance
    
	soundEvents[eventName] = eventInst;
}

void SoundSystem::playMusicEvent(string c) {
    if (musicPlay) {
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(musicInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            musicInstance = soundEvents.find(c) -> second;
            ERRCHECK(FMOD_Studio_EventInstance_Start(musicInstance));
        }
    }
    else {
        FMOD_STUDIO_EVENTINSTANCE * instance;
        instance = soundEvents.find(c) -> second;
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(instance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(instance));   
            musicInstance = instance;
            musicPlay = true;
        }
    }
}

void SoundSystem::stopMusicEvent(){
    if(musicInstance != nullptr){
        if(musicPlay){
            ERRCHECK(FMOD_Studio_EventInstance_Stop(musicInstance, FMOD_STUDIO_STOP_IMMEDIATE));
            musicInstance = nullptr;
            musicPlay = false;
        }
    }
}
void SoundSystem::playVoiceEvent(string c) {
    if (voicePlay) {
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(voiceInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            voiceInstance = soundEvents.find(c) -> second;
            ERRCHECK(FMOD_Studio_EventInstance_Start(voiceInstance));
        }
    }
    else {
        FMOD_STUDIO_EVENTINSTANCE * instance;
        instance = soundEvents.find(c) -> second;
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(instance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(instance));  
            voiceInstance = instance;
            voicePlay = true; 
        }
    }
}

void SoundSystem::stopVoiceEvent(){
    if(voiceInstance != nullptr){
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(voiceInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_PLAYING) {
            ERRCHECK(FMOD_Studio_EventInstance_Stop(voiceInstance, FMOD_STUDIO_STOP_IMMEDIATE));
            voiceInstance = nullptr;
            voicePlay = false;
        }
    }
}

void SoundSystem::playSFXEvent(string c) {
    if (sfxPlay) {
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(sfxInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            sfxInstance = soundEvents.find(c) -> second;
            ERRCHECK(FMOD_Studio_EventInstance_Start(sfxInstance));
        }
    }
    else {
        FMOD_STUDIO_EVENTINSTANCE * instance;
        instance = soundEvents.find(c) -> second;
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(instance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
            ERRCHECK(FMOD_Studio_EventInstance_Start(instance));  
            sfxInstance = instance;
            sfxPlay = true; 
        }
    }
}

void SoundSystem::stopSFXEvent(){
    if(sfxInstance != nullptr){
        ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(sfxInstance, &state));
        if (state == FMOD_STUDIO_PLAYBACK_PLAYING) {
            ERRCHECK(FMOD_Studio_EventInstance_Stop(sfxInstance, FMOD_STUDIO_STOP_IMMEDIATE));
            sfxInstance = nullptr;
            sfxPlay = false;
        }
    }
}

void SoundSystem::playEvent(SoundEvent* event) {
	event -> start();					
}

void SoundSystem::stopEvent(SoundEvent* event) {
    event -> stop();
}

void SoundSystem::checkAndStopEvent(SoundEvent* event) {
    if (event -> isPlaying()) event -> stop();
}

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

void SoundEvent::setVolume(f32 volumeData) {
    ERRCHECK(FMOD_Studio_EventInstance_SetVolume(soundInstance, volumeData));
}

void SoundEvent::setGain(f32 gainData) {
    ERRCHECK(FMOD_Studio_EventInstance_SetPitch(soundInstance, gainData));
}

void SoundEvent::setPosition(Vector3<f32> vectorData) {

}

bool SoundEvent::isPlaying() {
    bool playing = false;
    FMOD_STUDIO_PLAYBACK_STATE state;
    ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(soundInstance, &state));
    if (state == 0) {
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

FMOD_STUDIO_EVENTINSTANCE* SoundEvent::Instance() {
    return soundInstance;
}