#include "EventSystem.h"

EventSystem::EventSystem() {
    Events = new std::map<Enumeration::EventType, std::function<void()>>();
}

EventSystem::~EventSystem() {
    delete Events;
}

void EventSystem::addEvent(Enumeration::EventType event, std::function<void()> function) {
    Events -> insert(std::make_pair(event, function));
}

void EventSystem::triggerEvent(Enumeration::EventType event) {
    auto function = Events -> find(event);
    function -> second();
}