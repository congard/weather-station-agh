#ifndef WEATHERSTATION_PARTITION_H
#define WEATHERSTATION_PARTITION_H

#include <string_view>
#include <memory>

namespace ws {
class Partition {
public:
    virtual ~Partition() = default;

    virtual void mount() = 0;
    virtual void unmount() = 0;

    /**
     * @param path The relative path.
     * @return The absolute path.
     */
    static std::string absolute(std::string_view mountPoint, std::string_view path);
};

using PartitionPtr = std::unique_ptr<Partition>;
}

#endif //WEATHERSTATION_PARTITION_H
