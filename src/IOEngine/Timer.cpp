#include "Timer.h"

Timer::Timer(f32 maxD, bool l) {
    maxDuration = maxD;
    elapsedTime = maxDuration;
    loop = l;
}

Timer::~Timer() {

}

bool Timer::tick() {
    if (elapsedTime <= 0.0) {
        callback();
        if (loop) restart();
        return true;
    } else {
        elapsedTime -= Window::Instance() -> getDeltaTime();
        return false;
    }
}

void Timer::restart() {
    elapsedTime = maxDuration;
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