#ifndef TIMER_H
#define TIMER_H

#include <Types.h>
#include "../GraphicEngine/Window.h"

class Timer {
    public:
        /**
         * @brief 
         * @param maxDuration
         * @param isLoop
         * @param autoStart
         */
        Timer(f32, bool = false, bool = true);

        /**
         * @brief 
         * 
         */
        ~Timer();

        /**
         * @brief start couting time
         * 
         */
        void start();

        /**
         * @brief restart the timer
         * 
         */
        void restart();

        /**
         * @brief pause the timer
         * 
         */
        void pause();

        /**
         * @brief stop the timer
         * 
         */
        void stop();

        /**
         * @brief count time
         */
        void tick();

        /**
         * @brief 
         * @param d 
         */
        void changeDuration(f32 d);

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
         * @brief is running
         * 
         * @return true 
         * @return false 
         */
        bool isRunning();

        /**
         * @brief is finished
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();
        
        /**
         * @brief Get the Elapsed Time
         * 
         * @return f32 
         */
        f32 getElapsedTime();
        
        /**
         * @brief Get the Remaining Time
         * 
         * @return f32 
         */
        f32 getRemainingTime();

        /**
         * @brief 
         * 
         */
         f32 getMaxDuration();
    private:
        bool loop;
        bool running;

        f32 maxDuration;
        f32 elapsedTime;

        std::function<void()> callback;
        
};
    
#endif