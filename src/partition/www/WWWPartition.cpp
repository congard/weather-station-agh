#include "WWWPartition.h"
#include "core/log.h"

#include <esp_vfs_fat.h>

LOG_TAG("WWWPartition");

namespace ws {
constexpr static auto partitionLabel = "www";

WWWPartition::WWWPartition()
    : m_handle() {}

void WWWPartition::mount() {
    if (isMounted()) {
        LOGI("Already mounted");
        return;
    }

    LOGI("Mounting FAT filesystem");

    esp_vfs_fat_mount_config_t cfg {
        .format_if_mount_failed = false,
        .max_files = 4,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
        .disk_status_check_enable = false
    };

    wl_handle_t h;
    auto err = esp_vfs_fat_spiflash_mount_rw_wl(MountPoint, partitionLabel, &cfg, &h);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
    }

    ESP_ERROR_CHECK(err);
}

void WWWPartition::unmount() {
    if (isMounted()) {
        ESP_ERROR_CHECK(esp_vfs_fat_spiflash_unmount_rw_wl(MountPoint, m_handle));
    }
}

bool WWWPartition::isMounted() {
    return esp_vfs_fat_info(MountPoint, nullptr, nullptr) == ESP_OK;
}
}
