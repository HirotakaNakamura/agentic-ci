#include "os/Scheduler.h"
#include <iostream>

namespace bsw { namespace os {

void Scheduler::init() {
    tasks_.clear();
    currentTick_ = 0;
    std::cout << "[RTOS] Scheduler initialized" << std::endl;
}

void Scheduler::registerTask(const Task& task) {
    tasks_.push_back(task);
    std::cout << "[RTOS] Task registered: " << task.getName() << std::endl;
}

void Scheduler::start() {
    std::cout << "[RTOS] Scheduler started with " << tasks_.size() << " tasks" << std::endl;
    for (auto& t : tasks_) {
        t.activate();
    }
}

void Scheduler::tick() {
    currentTick_++;
    for (auto& t : tasks_) {
        if (t.getState() == TaskState::READY) {
            t.execute();
        }
    }
}

uint32_t Scheduler::getTaskCount() const {
    return static_cast<uint32_t>(tasks_.size());
}

}} // namespace bsw::os
