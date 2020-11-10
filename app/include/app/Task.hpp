#pragma once

#include <atomic>

namespace App {

    /// An enum of different task return-types.
    /// @note types map to uint8_t
    enum class TaskStatus: uint8_t {
        DONE   = 0, 
        PAUSED = 1,
        FAILED = 2, 
    };
    
    class Task {
        public:
            bool taskDone = false;
            
        public:
            /// No copy constructors allowed
            Task(Task* task) = delete;
            Task(Task& task) = delete;

            /**
             * @brief Run the task until done or flag is raised
             * 
             * @param flag Atomic flag to indicate messages recieved
             * 
             * @returns Task exit code (0: done, 1: paused, 2: failed)
             */
            TaskStatus run(std::atomic<bool>& flag);

        private:
            /**
             * @brief Run one iteration of the main task loop
             * 
             * @returns Task done
             */
            virtual bool _run() = 0;
    };

}
