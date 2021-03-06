/*
 * This file defines a few things for
 * interfacing with a 4MiB memory-mapped flash
 * chip that is byte-addressable
 */

#define FLASH_SECTOR_SIZE    (4096)
#define FLASH_NUM_SECTORS    (1024)
#define FLASH_TOTAL_SIZE     (FLASH_SECTOR_SIZE * FLASH_NUM_SECTORS)

// A generic struct for NOR flash, containing
// a vendor ID and all operations that can be performed on it
struct nor_flash {
  int vendor_id;
  void * operations;
}

