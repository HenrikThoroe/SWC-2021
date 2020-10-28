#include "EventLoop.hpp"

/**
 * @brief Main function of the client and starting point of program flow
 * 
 * @param argc Number of arguments passed
 * @param argv Array of pointers to argument strings (first argument is own filename)
 * 
 * @return Exit status code
 */
int main(int argc, char* argv[]) {
    App::EventLoop loop(argc, argv);
    loop.run();
    
    return 0;
}
