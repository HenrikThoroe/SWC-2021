#pragma once 

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Util::Log {

    /// Flags to set the log-stream destination file
    enum class OutputFile {
        DEFAULT,
        SENT,
        RECEIVED
    };

    /// Manages and writes data to specified log files.
    class FileStream {
        private:
            std::ofstream file;

            OutputFile fileType;

        public:
            FileStream(const OutputFile& fileType);

            ~FileStream();
            
            void operator << (const std::string& data) {
                #ifndef NOLOG
                file << data;
                #endif
            }

            void operator << (const char* data) {
                #ifndef NOLOG
                file << data;
                #endif
            }

            void operator << (const int& data) {
                #ifndef NOLOG
                file << data;
                #endif
            }

            void operator << (const uint8_t& data) {
                #ifndef NOLOG
                file << static_cast<int>(data);
                #endif
            }

        private:
            /// Finds the path, where the file should be placed, and creates all required directories.
            static const std::string& getDirectoryPath();
    };

    /// A FileStream writing to the default log file
    inline FileStream out(OutputFile::DEFAULT);

    /**
     * @brief A FileStream writing to the "sent" log file
     * @note The stream should be only fed with XML strings sent to the server.
     */
    inline FileStream sent(OutputFile::SENT);

    /**
     * @brief A FileStream writing to the "received" log file
     * @note The stream should be only fed with XML strings received from the server.
     */
    inline FileStream received(OutputFile::RECEIVED);

}
