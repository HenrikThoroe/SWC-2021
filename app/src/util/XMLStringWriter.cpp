#include "XMLStringWriter.hpp"

#include "pugixml.hpp"

namespace Util {
    void XMLStringWriter::write(const void *data, size_t size) {
        result.append(static_cast<const char *>(data), size);
    }
} // namespace Util