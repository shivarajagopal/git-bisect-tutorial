#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

#include "flasher.h"
#include "flash_memory.h"

extern struct nor_flash * nor_flash_dev;

/* @brief
 * Format the NOR flash
 */
static int prv_flasher_format(void)
{
  printf("Formatting flash storage...");
  nor_flash_dev->operations.format();
}

/* @brief
 * Write the given data to NOR flash
 */
static int prv_flasher_write(void)
{
  printf("Writing memory to flash...");
  int sector_to_write = *(volatile int *) DATA_SECTOR_ADDR;
  size_t size = *(size_t *) DATA_SIZE_ADDR;
  return nor_flash_dev->operations.write(sector_to_write, DATA_PAYLOAD_ADDR, size)
}

/* @brief
 * Read the specified data from NOR flash
 */
static int prv_flasher_read(void)
{
  printf("Reading memory from flash...");
  int sector_to_read = *(volatile int *) DATA_SECTOR_ADDR;
  size_t size = *(size_t *) DATA_SIZE_ADDR;
  return nor_flash_dev->operations.read(sector_to_read, size);
}

/* @brief
 * Verify the given data from NOR flash
 */
static int prv_flasher_verify(void)
{
  printf("Verifying flash memory against input data...");
  int sector_to_compare = *(volatile int *) DATA_SECTOR_ADDR;
  size_t size = *(size_t *) DATA_SIZE_ADDR;
  uint8_t readback_data[size];
  nor_flash_dev->operations.read(sector_to_compare, size);
  int return_code = memcmp((void *) DATA_PAYLOAD_ADDR, readback_data, size);
  return (return_code >= 0)
}

/* @brief
 * Initialize the flasher utility, including any
 * storage that will be needed for flashing
 */
int flasher_init(void)
{
  printf("Initialize flash storage...");
  return nor_flash_dev->operations.init(NULL);
}

/* @brief
 * Run the flasher utility with the given command
 */
int flasher_run(uint32_t command)
{
  enum memory_commands flasher_command = (enum memory_commands) command;
  int return_code = 0;
  switch(command)
  {
    case memory_format:
      return_code = flasher_format();
      break;
    case memory_write:
      return_code = flasher_write();
      break;
    case memory_read:
      return_code = flasher_read();
      break;
    case memory_verify:
      return_code = flasher_verify();
      break;
    default:
      assert(false);
  }
  return 0;
}
