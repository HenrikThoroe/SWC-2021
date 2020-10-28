#pragma once

#include "pugixml.hpp"

namespace Util {

    /// Utility struct used for converting XMLs to string with pugixml.
    struct XMLStringWriter : pugi::xml_writer {
        /// The string that contains the XML.
        std::string result;

        /**
         * @brief Adds the XML data to the internal string.
         * 
         * @param data The XML data.
         * @param size The size of the XML data.
         */
        virtual void write(const void* data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    };

}
