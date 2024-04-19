#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class GameTimer {
public:
    GameTimer(int minutes);

    void reset(int minutes);

    bool isTimeUp() const;
    int getRemainingSeconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};

#endif // TIME_HPP
