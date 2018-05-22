#include "EventSystem.h"

EventSystem::EventSystem() {
    Events = new std::map<std::string, std::function<void()>>();
}

EventSystem::~EventSystem() {
    delete Events;
}

/*
* Save a pair of an event and a function on the hash map Events
* The event must be a type of EventType declared on the Enumeration.h file
* The function must be static, void and without parameters
*/
void EventSystem::addEvent(std::string event, std::function<void()> function) {
    Events -> insert(std::make_pair(event, function));
}

/*
* Search an event on the hash map Events and call the function related with the event
* The event must be a type of EventType declared on the Enumeration.h file.
*/
void EventSystem::triggerEvent(std::string event) {
    auto function = Events -> find(event);
    function -> second();
}