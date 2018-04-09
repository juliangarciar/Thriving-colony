#include "Timer.h"

Timer::Timer(f32 maxD, bool l) {
    maxDuration = maxD;
    elapsedTime = maxDuration;
    loop = l;
}

Timer::~Timer() {

}

bool Timer::tick() {
    //std::cout << elapsedTime << "/" << maxDuration << std::endl;
    if (elapsedTime <= 0.0) {
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

f32 Timer::getElapsedTime() {
    return elapsedTime;
}

f32 Timer::getMaxDuration() {
    return maxDuration;
}
