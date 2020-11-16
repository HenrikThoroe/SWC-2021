#pragma once

#include <string>
#include <inttypes.h>

namespace Util::Print::Text {

    /// An enum indicating how text should be aligned
    enum class TextAlignment {
        LEFT,
        CENTER, 
        RIGHT
    };

    /// Flags for specifying a time unit
    enum class TimeUnit : uint8_t {
        NS = 0, 
        US = 1, 
        MS = 2, 
        S  = 3
    };

    /**
     * @brief Creates a string with fixed width
     * @param str The source string which should be extended or shrinked to the passed width
     * @param width The final width (length) of the string 
     * @param align Flag which sets how whitespace should be attached to `str`
     * @return A string build from `str` with length of `width`
     */
    std::string fixedWidth(std::string str, uint32_t width, TextAlignment align);

    /**
     * @brief Repeats the given character 'count' times
     * @param character The character to repeat
     * @param count The number of repetition
     */
    std::string repeat(char character, uint32_t count);

    /**
     * @brief Formats a floating point number and returns the formatted string
     * @param number The number which should be represented as string
     * @param fixed The number of decimal places of `number`
     * @param thousandSeperator The character which seperates every third digit of the integer part
     * @return The formatted string representation of `number`
     */
    std::string formatDouble(double number, uint8_t fixed = 3, char thousandSeperator = '_');

    /**
     * @brief Formats an integer and returns the formatted string
     * @param number The number which should be represented as string
     * @param thousandSeperator The character which seperates every third digit of the integer
     * @return The formatted string representation of `number`
     */
    std::string formatInt(int number, char thousandSeperator = '_');

    /**
     * @brief Formats the given time as string
     * @param baseUnit The unit of `time`s value. Can be nanosecond up to second
     * @param thousandSeperator The character which seperates every third digit of the integer
     */
    std::string formatTime(uint64_t time, TimeUnit baseUnit, char thousandSeperator = '_');

}
