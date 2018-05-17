#include "IO.h"

IO* IO::pinstance = 0;

IO* IO::Instance() {
    if (pinstance == 0) {
        pinstance = new IO();
    }
    return pinstance;
}

IO::IO() {
    cursor = new Mouse();
    keyboard = new Keyboard();

    events = new EventSystem();

    resourceManager = new ResourceManager();
}

IO::~IO(){
    delete cursor;
    delete keyboard;
    delete events;
    delete resourceManager;
}

void IO::Update(){
    cursor -> refreshStates();
	for (int i = 0; i < timers.size(); i++){
		timers[i]->tick();
	}
}

void IO::registerTimer(Timer* t){
	timers.push_back(t);
}

void IO::unregisterTimer(Timer* t){
	std::vector<Timer*>::iterator it = std::find(timers.begin(), timers.end(), t);
	if (it != timers.end()){
		timers.erase(it);
	}
}

Keyboard *IO::getKeyboard(){
    return keyboard;
}

Mouse *IO::getMouse() {
    return cursor;
}

EventSystem *IO::getEventManager() {
    return events;
}

ResourceManager *IO::getResourceManager(){
    return resourceManager;
}