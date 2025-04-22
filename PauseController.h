#pragma once
#include <mutex>
#include <condition_variable>

struct PauseController {
    std::mutex mtx;
    std::condition_variable cv;
    bool isPaused = false;
};
