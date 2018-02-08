#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include <functional>
#include "../Enumeration.h"
#include <Types.h>

class EventSystem {

    public:
        EventSystem();
        ~EventSystem();
        
        void triggerEvent(Enumeration::EventType);
        void addEvent(Enumeration::EventType, std::function<void()>);
        
    private:
        std::map<Enumeration::EventType, std::function<void()>> *Events;
};

#endif