#ifndef WEATHERSTATION_WWWPARTITION_H
#define WEATHERSTATION_WWWPARTITION_H

#include "partition/Partition.h"

namespace ws {
class WWWPartition : public Partition {
public:
    constexpr static auto MountPoint = "/www";

public:
    WWWPartition();

    void mount() override;
    void unmount() override;

private:
    static bool isMounted();

private:
    int32_t m_handle;
};
}

#endif //WEATHERSTATION_WWWPARTITION_H
