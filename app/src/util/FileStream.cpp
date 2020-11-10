#include <filesystem>
#include <ctime>

#include "FileStream.hpp"

namespace Util::Log {

    FileStream::FileStream(const OutputFile& fileType) : fileType(fileType) {
        const std::string& path = FileStream::getDirectoryPath();

        switch (fileType) {
            case OutputFile::DEFAULT:
                file.open(path + "/log.txt");
                break;
            case OutputFile::SENT:
                file.open(path + "/sent.txt");
                break;
            case OutputFile::RECEIVED:
                file.open(path + "/receive.txt");
                break;
        }
    }

    const std::string& FileStream::getDirectoryPath() {
        static std::string path = "";

        if (path.size() == 0) {
            const time_t time = std::time(0);
            const std::tm* localTime = std::localtime(&time);
            const int year = localTime->tm_year;
            const int month = localTime->tm_mon;
            const int day = localTime->tm_mday;
            const int hour = localTime->tm_hour;
            const int minute = localTime->tm_min;
            uint32_t subfolder = 0;
            const std::string dirName = 
                std::to_string(month) + "-" + 
                std::to_string(day) + "-" + 
                std::to_string(year) + "_" + 
                std::to_string(hour) + "-" + 
                std::to_string(minute);

            if (!std::filesystem::exists("logs")) {
                std::filesystem::create_directory("logs");
            }

            if (!std::filesystem::exists("logs/" + dirName)) {
                std::filesystem::create_directory("logs/" + dirName);
            }

            while (std::filesystem::exists("logs/" + dirName + "/" + std::to_string(subfolder))) {
                subfolder += 1;
            }

            path = "logs/" + dirName + "/" + std::to_string(subfolder);

            std::filesystem::create_directory(path);
        }

        return path;
    }

    FileStream::~FileStream() {
        file.close();
    }

}
