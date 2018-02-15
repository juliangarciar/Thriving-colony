//  Created by Pierre on 20171022.
//  Edited and completed by Julian Garcia Ruiz.

#ifndef SoundSystem_h
#define SoundSystem_h

#include <map>
#include <string>
#include <fmod/fmod.hpp>
#include <fmod/fmod_studio.h>
#include <fmod/fmod_errors.h>
#include <Types.h>
#include <MathEngine/Vector3.h>

using namespace std;
using namespace FMOD;

class SoundEvent;

class SoundSystem {
	
public:
    static SoundSystem* Instance();
    /**
     *  Constructor
     *  \param soundBanksPath ruta del directorio donde se encuentran los bancos generados con FMOD Studio
     */
	SoundSystem();
    
	~SoundSystem();
    /*
    *   Inits the sytem (events and descriptions)
    */
	void initSystem();
    /**
     *  Método factoría que Construye un SoundEvent a partir del nombre de un evento de FMOD Studio, 
     *  p. ej. "event:/Ambience/Country"
     *
     *  \param eventPath nombre del evento según la nomenclatura de FMOD Studio
     */
    FMOD_STUDIO_EVENTINSTANCE* getEvent(string eventPath);
    
    /**
     *  Modifica el volumen general del motor de sonido
     */
    void setVolume(f32 vol);
    
    /**
     *  Modifica la posición del punto de escucha (en esta aplicación sólo hay uno)
     */
    void setListernerPosition(Vector3<f32> pos);
    
    /**
     *  Actualiza el motor de audio
     *  \param paused indica si hay que pausar el motor de audio o no
     */
    void update();
    FMOD_STUDIO_EVENTDESCRIPTION* createDescription(const char* path, FMOD_STUDIO_EVENTDESCRIPTION* desc);
    void createEvent(std::string eventPath);

    void playEvent(SoundEvent* event);
    void playMusicEvent(string c);
    void playVoiceEvent(string c);
    void stopEvent(SoundEvent* event);
    void checkAndStopEvent(SoundEvent* event);
    
    void setStat(bool data);

private:
    static SoundSystem* pinstance;
    bool paused;
    bool voicePlay = false;
    bool musicPlay = false;
    //bool playing = false;
    //const char * systemID;
    //FMOD_RESULT result;
    //FMOD_STUDIO_STOP_MODE pausedMode;
    FMOD_GUID id;
    FMOD_STUDIO_BUS*        bus = 0;
	FMOD_STUDIO_PLAYBACK_STATE state;
    FMOD_STUDIO_SYSTEM*	system = 0;
	FMOD_SYSTEM* lowLevelSystem = 0;
	FMOD_STUDIO_BANK* masterBank = 0;
	FMOD_STUDIO_BANK* stringsBank = 0;
    FMOD_STUDIO_BANK* droraniaBank = 0;
    FMOD_STUDIO_BANK* kaonovBank = 0;
    map<string, FMOD_STUDIO_BANK*> banks;
    map<string, FMOD_STUDIO_EVENTDESCRIPTION*> eventDescriptions;
    map<string, FMOD_STUDIO_EVENTINSTANCE*> soundEvents;
    FMOD_STUDIO_EVENTINSTANCE* musicInstance = 0;
    FMOD_STUDIO_EVENTINSTANCE* voiceInstance = 0;
    //FMOD_STUDIO_EVENTINSTANCE * sfxInstance;
};

//THIS IS GOING TO DISSAPEAR
class SoundEvent {
public:
    SoundEvent();
    ~SoundEvent();    
    void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *EventInstance);
    /**
     *  Comienza a reproducir el evento
     */
    virtual void start();
    
    /**
     *  Detiene la reproducción del evento inmediatamente
     */
    void stop();
    
    /**
     *  Pausa la reproducción del evento. 
     *  Para continuar la reproducción, usar start()
     *  \sa start()
     */
    void pause();
    
    /**
     *  Modifica el volumen del evento
     *  \param vol volumen del evento: 0=silencio, 1=máximo volumen
     */
    void setVolume(f32 vol);
    
    /**
     *  Modifca el volumen del evento multiplicando por un factor de ganancia
     *  \param gain factor de ganancia. 0=silencio, 1=mantener el volumen
     */
    void setGain(f32 gain);
    
    /**
     *  Modifica la posición 3D del evento de sonido
     *  \param pos nuevo vector de posición
     */
    void setPosition(Vector3<f32> pos);
    
    /**
     *  Consulta si el evento está sonando
     *  \return devuelve cierto si el evento está sonando
     */
    bool isPlaying();
    
    void release();
    FMOD_STUDIO_EVENTINSTANCE* Instance();
private:
    FMOD_STUDIO_EVENTINSTANCE *soundInstance;
    /**
     * Este método crea un SoundEvent (EngineSound, WindSound, etc.) correspondiente
     * al evento que recibe como argumento
     */
    
};


#endif /* SoundSystem_h */