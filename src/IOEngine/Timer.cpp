#include "Timer.h"

Timer::Timer(f32 maxD, bool l, bool a) : maxDuration(maxD), loop(l), 
    elapsedTime(0), running(false), callback(nullptr) 
{
    if (a) start();
}

Timer::~Timer() {
    //ToDo: free callback?
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

f32 Timer::getElapsedTime() {
    return elapsedTime;
}

f32 Timer::getRemainingTime() {
    return maxDuration - elapsedTime;
}

f32 Timer::getMaxDuration() {
    return maxDuration;
}