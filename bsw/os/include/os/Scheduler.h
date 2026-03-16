#pragma once
#include "os/Task.h"
#include <vector>

namespace bsw { namespace os {

class Scheduler {
public:
    void init();
    void registerTask(const Task& task);
    void start();
    void tick();
    uint32_t getTaskCount() const;

private:
    std::vector<Task> tasks_;
    TickType currentTick_ = 0;
};

}} // namespace bsw::os
