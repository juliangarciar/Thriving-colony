#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include <functional>
#include "../Enumeration.h"

class EventSystem {

    public:
        EventSystem();
        ~EventSystem();
        
        void triggerEvent();
        void addEvent(Enumeration::EventType, std::function<void()>);
        
    private:
        std::map<Enumeration::EventType, std::function<void()>> *Events;
};

#endif