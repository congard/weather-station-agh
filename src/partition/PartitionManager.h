#ifndef WEATHERSTATION_PARTITIONMANAGER_H
#define WEATHERSTATION_PARTITIONMANAGER_H

#include "Partition.h"

#include <vector>

namespace ws {
class PartitionManager {
public:
    PartitionManager();
    ~PartitionManager();

    void mount();
    void unmount();

    void add(PartitionPtr partition);

    template<typename T, typename ...Args>
    void add(Args&&... args) {
        add(std::make_unique<T>(std::forward<Args>(args)...));
    }

private:
    std::vector<PartitionPtr> m_partitions;
};
}

#endif //WEATHERSTATION_PARTITIONMANAGER_H
