#include "Timer.h"

Timer::Timer(f32 maxD) {
    maxDuration = maxD;
    elapsedTime = maxDuration;
}

Timer::~Timer() {

}

bool Timer::tick() {
    //std::cout << elapsedTime << "/" << maxDuration << std::endl;
    if (elapsedTime <= 0.0) {
        restart();
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
