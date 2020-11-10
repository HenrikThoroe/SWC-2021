#include <atomic>

#include "Task.hpp"

namespace App {
    
    TaskStatus Task::run(std::atomic<bool>& flag) {
        while (true) {
            // Check if message was recieved and task has to pause
            if (flag) return TaskStatus::PAUSED;

            try {
                // Run task iteration and return if done
                if (_run()) return TaskStatus::DONE;
            } catch (...) {
                // Catch all exceptions and let task return with exception
                return TaskStatus::FAILED;
            }
        }
    }

}
