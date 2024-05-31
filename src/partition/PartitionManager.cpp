#include "PartitionManager.h"
#include "www/WWWPartition.h"

namespace ws {
PartitionManager::PartitionManager() {
    add<WWWPartition>();
}

PartitionManager::~PartitionManager() {
    unmount();
}

void PartitionManager::mount() {
    for (auto &partition : m_partitions) {
        partition->mount();
    }
}

void PartitionManager::unmount() {
    for (auto &partition : m_partitions) {
        partition->unmount();
    }
}

void PartitionManager::add(PartitionPtr partition) {
    m_partitions.emplace_back(std::move(partition));
}
}
