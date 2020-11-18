#include <math.h>

#include "stringTools.hpp"

namespace Util::Print::Text {

    std::string fixedWidth(std::string str, uint32_t width, TextAlignment align) {
        if (str.length() > width) {
            return str.substr(0, width);
        }

        bool addLeft = true;

        while (str.length() < width) {
            switch (align) {
                case TextAlignment::LEFT:
                    str.append(" ");
                    break;

                case TextAlignment::RIGHT:
                    str.insert(0, " ");
                    break;
                case TextAlignment::CENTER:
                    if (addLeft) {
                        str.append(" ");
                    } else {
                        str.insert(0, " ");
                    }

                    addLeft = !addLeft;
                    break; 
            }
        }

        return str;
    }

    std::string repeat(char character, uint32_t count) {
        std::string out;

        while (out.length() < count) {
            out += character;
        }

        return out;
    }

    std::string formatInt(int number, char thousandSeperator) {
        std::string out = std::to_string(number);
        std::string seperator = std::string(1, thousandSeperator);

        for (int i = out.length() - 3; i > 0; i -= 3) {
            out.insert(i, seperator);
        }

        return out;
    }

    std::string formatDouble(double number, uint8_t fixed, char thousandSeperator) {
        std::string str = std::to_string(number);
        std::string intPart = formatInt(static_cast<int>(number), thousandSeperator);
        std::string floatPart = str.substr(str.find_first_of('.') + 1);
        std::string out = intPart + ".";

        if (floatPart.length() > fixed) {
            out += floatPart.substr(0, fixed);
        } else {
            out += floatPart + repeat('0', fixed - floatPart.length());
        }

        return out;
    }

    std::string formatTime(uint64_t time, TimeUnit baseUnit, char thousandSeperator) {
        uint8_t unit = static_cast<uint8_t>(baseUnit);
        uint8_t decimals = 0;
        double factor = 1;
        std::string suffix;

        while (static_cast<TimeUnit>(unit) != TimeUnit::S && time * factor >= 1000) {
            unit += 1;
            decimals = 3;
            factor *= pow(10, -3);
        }

        switch (static_cast<TimeUnit>(unit)) {
            case TimeUnit::NS:
                suffix = "ns";
                break;
            case TimeUnit::US:
                suffix = "us";
                break;
            case TimeUnit::MS:
                suffix = "ms";
                break;
            case TimeUnit::S:
                suffix = "s";
                break;
        }

        if (decimals == 0) {
            return formatInt(static_cast<int>(time), thousandSeperator) + suffix;
        } else {
            return formatDouble(static_cast<double>(time) * factor, decimals, thousandSeperator) + suffix;
        }
    }

    std::string bold(std::string text) {
        return "\033[1;37m" + text + "\033[0m";
    }

    std::string color(std::string text, TextColor color) {
        switch (color) {
            case TextColor::RED:
                text.insert(0, "\033[31m");
                break;
            case TextColor::GREEN:
                text.insert(0, "\033[32m");
                break;
            case TextColor::BLUE:
                text.insert(0, "\033[34m");
                break;
        }

        return text + "\033[0m";
    }

}
