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