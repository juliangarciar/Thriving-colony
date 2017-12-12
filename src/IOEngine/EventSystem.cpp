#include "EventSystem.h"

EventSystem::EventSystem() {
    Events = new std::map<Enumeration::EventType, std::function<void()>>();
}

EventSystem::~EventSystem() {
    delete Events;
}

/*
* Save a pair of an event and a function on the hash map Events
* The event must be a type of EventType declared on the ../Enumeration.h file
* The function must be static, void and without parameters
*/
void EventSystem::addEvent(Enumeration::EventType event, std::function<void()> function) {
    Events -> insert(std::make_pair(event, function));
}

/*
* Search an event on the hash map Events and call the function related with the event
* The event must be a type of EventType declared on the ../Enumeration.h file.
*/
void EventSystem::triggerEvent(Enumeration::EventType event) {
    auto function = Events -> find(event);
    function -> second();
}