#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include <functional>
#include <Enumeration.h>
#include <Types.h>

class EventSystem {
    public:
        EventSystem();
        ~EventSystem();
        
        void triggerEvent(std::string);
        void addEvent(std::string, std::function<void()>);
        
    private:
        std::map<std::string, std::function<void()>> *Events;
};

#endif