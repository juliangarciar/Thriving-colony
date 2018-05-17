#include "Timer.h"
#include "IO.h"
#include "../GraphicEngine/Window.h"

Timer::Timer(f32 maxD, bool l, bool a) : loop(l), running(false),
<<<<<<< HEAD
maxDuration(maxD), elapsedTime(0), callback(nullptr) 
=======
	maxDuration(maxD), elapsedTime(0), callback(nullptr) 
>>>>>>> master
{
	IO::Instance()->registerTimer(this);
    if (a) start();
}

Timer::~Timer() {
	IO::Instance()->unregisterTimer(this);
}

void Timer::start(){
    running = true;
}

void Timer::restart() {
    elapsedTime = 0;
    running = true;
}

void Timer::pause(){
    running = false;
}

void Timer::stop(){
    elapsedTime = 0;
    running = false;
}

void Timer::tick() {
    if (running){
        if (maxDuration >= 0 && elapsedTime >= maxDuration){
            if (callback != nullptr) callback();
            if (loop) restart();
            else running = false;
            return;
        }
        elapsedTime += Window::Instance() -> getDeltaTime();
    }
}

void Timer::changeDuration(f32 d) {
    maxDuration = d;
}

void Timer::setCallback(std::function<void()> c){
    callback = c;
}

void Timer::triggerCallback(){
    callback();
}

bool Timer::isRunning(){
    return running;
}

bool Timer::isFinished(){
    return (elapsedTime >= maxDuration && !loop);
}

f32 Timer::getElapsedTime() {
    return elapsedTime;
}

f32 Timer::getRemainingTime() {
    return maxDuration - elapsedTime;
}

f32 Timer::getMaxDuration() {
    return maxDuration;
}