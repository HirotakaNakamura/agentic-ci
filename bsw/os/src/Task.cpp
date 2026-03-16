#include "os/Task.h"
#include <iostream>

namespace bsw { namespace os {

Task::Task(TaskId id, const std::string& name, Priority prio, std::function<void()> entryPoint)
    : id_(id), name_(name), priority_(prio), state_(TaskState::SUSPENDED), entry_(entryPoint) {}

TaskId Task::getId() const { return id_; }
const std::string& Task::getName() const { return name_; }
TaskState Task::getState() const { return state_; }

void Task::activate() {
    state_ = TaskState::READY;
    std::cout << "[RTOS] Task " << name_ << " (id=" << id_ << ") activated" << std::endl;
}

void Task::suspend() {
    state_ = TaskState::SUSPENDED;
}

void Task::execute() {
    state_ = TaskState::RUNNING;
    if (entry_) {
        entry_();
    }
    state_ = TaskState::READY;
}

}} // namespace bsw::os
