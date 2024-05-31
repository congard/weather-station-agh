#include "Partition.h"

#include <string>

namespace ws {
std::string Partition::absolute(std::string_view mountPoint, std::string_view path) {
    std::string abs;
    abs += mountPoint;
    abs += "/";
    abs += path;
    return abs;
}
}
