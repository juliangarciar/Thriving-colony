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

        /**
         * @brief Get the Elapsed Time object
         * 
         * @return f32 
         */
        f32 getElapsedTime();

        /**
         * @brief 
         * 
         */
         f32 getMaxDuration();

    private:
        bool loop;

        f32 maxDuration;
        f32 elapsedTime;
        
};
    
#endif