#ifndef TIMER_H
#define TIMER_H

#include <Types.h>
#include "../GraphicEngine/Window.h"

class Timer {
    public:
        /**
         * @brief 
         * 
         * @param maxD 
         */
        Timer(f32, bool = true);

        /**
         * @brief 
         * 
         */
        ~Timer();

        /**
         * @brief Set the Callback object
         * 
         */
        void setCallback(std::function<void()>);

        /**
         * @brief 
         * 
         */
        void triggerCallback();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool tick();
        
        /**
         * @brief 
         * 
         */
        void restart();

        /**
         * @brief 
         * 
         * @param d 
         */
        void changeDuration(f32 d);

    private:
        bool loop;

        f32 maxDuration;
        f32 elapsedTime;

        std::function<void()> callback;
        
};
    
#endif