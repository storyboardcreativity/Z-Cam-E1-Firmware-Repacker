#include <stdint.h>

// WARNING! ALL THESE DEFINES AND TYPES ARE USEFUL ONLY FOR Z-Cam E1 CAMERA FW FILE!

#define FW_PARTITION_COUNT 15
#define PARTITION_HEADER_MAGIC 0xA324EB90

#define INI_SECTION__FW_HEADER "firmware_header"
#define INI_SECTION_PREFIX__PARTITION "partition : "
#define INI_SECTION__UNKNOWN_DATA "unknown_data"

#define INI_SECTION__FW_HEADER__MODEL_NAME "model_name"
#define INI_SECTION__FW_HEADER__VERSION_MAJOR "version_major"
#define INI_SECTION__FW_HEADER__VERSION_MINOR "version_minor"

#define INI_SECTION__PARTITION__ENABLED "enabled"
#define INI_SECTION__PARTITION__SIZE_IN_MEMORY "size_in_memory"
#define INI_SECTION__PARTITION__OFFSET_IN_MEMORY "offset_in_memory"
#define INI_SECTION__PARTITION__DATE_DAY "date_day"
#define INI_SECTION__PARTITION__DATE_MONTH "date_month"
#define INI_SECTION__PARTITION__DATE_YEAR "date_year"
#define INI_SECTION__PARTITION__SOURCE_FILE_NAME "source_file_name"

const char* default_model_name = "E1";

const char* output_folder_name = "E1_fw_unpacked";
const char* output_file_name = "E1_fw_packed.bin";

const char* unpacked_firmware_settings_name = "firmware_info.ini";

const char* partition_names[FW_PARTITION_COUNT]
{
    "Bootstrap",
    "Partition Table",
    "Bootloader",
    "SD Firmware Update Code",
    "System Software",
    "DSP uCode",
    "System ROM Data",
    "Linux Kernel",
    "Linux Root FS",
    "Linux Hibernation Image",
    "Storage 1",
    "Storage 2",
    "Index For Video Recording",
    "User Settings",
    "Calibration Data"
};

const uint32_t partition_default_sizes_in_memory[FW_PARTITION_COUNT]
{
    0x800,
    0x40000,
    0x40000,
    0x100000,
    0x2000000,
    0x500000,
    0xF00000,
    0xA00000,
    0x3C00000,
    0x1E00000,
    0x0,
    0x500000,
    0xC00000,
    0x40000,
    0x100000
};

#pragma pack (push, 1)
struct firmware_file_header
{
    firmware_file_header()
    {
        for (int i = 0; i < 32; ++i)
            model_name[i] = '\0';
        version_major = 0;
        version_minor = 0;
        for (int i = 0; i < FW_PARTITION_COUNT; ++i)
        {
            partition_infos[i].size_in_fw_file = 0;
            partition_infos[i].crc32 = 0;
            partition_sizes_in_memory[i] = 0;
        }
        bluetooth_fw_partition_size = 0;
        for (int i = 0; i < 7; ++i)
            unknown[i] = 0;
        crc32 = 0;
    }

    uint8_t model_name[32];
    uint32_t version_major;
    uint32_t version_minor;
    struct
    {
        uint32_t size_in_fw_file;
        uint32_t crc32;
    } partition_infos[FW_PARTITION_COUNT];
    uint32_t partition_sizes_in_memory[FW_PARTITION_COUNT];
    uint32_t bluetooth_fw_partition_size;
    uint32_t unknown[7];                        // Unknown field
    uint32_t crc32;
};
#pragma pack (pop)

#pragma pack (push, 1)
struct partition_header
{
    partition_header()
    {
        crc32 = 0;
        __unk0 = 0;
        date_day = 0;
        date_month = 0;
        date_year = 0;
        data_size = 0;
        offset_in_device_memory = 0;
        __unk1 = 0;
        magic = PARTITION_HEADER_MAGIC;
        for (int i = 0; i < 228; ++i)
            __padding[i] = 0x00;
    }

    uint32_t crc32;
    uint32_t __unk0;
    uint8_t date_day;
    uint8_t date_month;
    uint16_t date_year;
    uint32_t data_size;
    uint32_t offset_in_device_memory;
    uint32_t __unk1;
    uint32_t magic;
    uint8_t __padding[228];
};
#pragma pack (pop)