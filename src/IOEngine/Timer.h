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
        Timer(f32 maxD);

        /**
         * @brief 
         * 
         */
        ~Timer();

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
        f32 maxDuration;
        f32 elapsedTime;
        
};
    
#endif