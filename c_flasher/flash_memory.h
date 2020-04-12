/*
 * This file defines a few things for
 * interfacing with a 4MiB memory-mapped flash
 * chip that is byte-addressable
 */

#define FLASH_MEM_START_ADDR (0x20000000)
#define FLASH_SECTOR_SIZE    (4096)
#define FLASH_NUM_SECTORS    (1024)
#define FLASH_TOTAL_SIZE     (FLASH_SECTOR_SIZE * FLASH_NUM_SECTORS)

