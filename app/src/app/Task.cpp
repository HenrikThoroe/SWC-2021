#include <atomic>

#include "Task.hpp"

namespace App {
    
    int Task::run(std::atomic<bool>& flag) {
        while (true) {
            // Check if message was recieved and task has to pause
            if (flag) return 1;

            try {
                // Run task iteration and return if done
                if (_run()) return 0;
            } catch (...) {
                // Catch all exceptions and let task return with exception
                return 2;
            }
        }
    }

}
