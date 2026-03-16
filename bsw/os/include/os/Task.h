#pragma once
#include "os/OsTypes.h"
#include <functional>
#include <string>

namespace bsw { namespace os {

class Task {
public:
    Task(TaskId id, const std::string& name, Priority prio, std::function<void()> entryPoint);

    TaskId getId() const;
    const std::string& getName() const;
    TaskState getState() const;
    void activate();
    void suspend();
    void execute();

private:
    TaskId id_;
    std::string name_;
    Priority priority_;
    TaskState state_;
    std::function<void()> entry_;
};

}} // namespace bsw::os
