#include "Time.hpp"
#include <cmath>

GameTimer::GameTimer(int minutes) {
    reset(minutes);
}

void GameTimer::reset(int minutes) {
    startTime = std::chrono::high_resolution_clock::now();
    endTime = startTime + std::chrono::minutes(minutes);
}

bool GameTimer::isTimeUp() const {
    auto currentTime = std::chrono::high_resolution_clock::now();
    return currentTime >= endTime;
}

int GameTimer::getRemainingSeconds() const {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> remaining = endTime - currentTime;
    return static_cast<int>(std::ceil(remaining.count()));
}
