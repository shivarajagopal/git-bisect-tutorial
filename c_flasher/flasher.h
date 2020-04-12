#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

enum memory_commands {
  memory_format = 0x00000000,
  memory_write  = 0x00000001,
  memory_read   = 0x00000002,
  memory_verify = 0x00000003,
};

#define COMMAND_ADDR        (0x10101000)
#define DATA_SECTOR_ADDR    (0x10102000)
#define DATA_ADDR           (0x10110000)
#define DATA_SIZE_ADDR      (DATA_ADDR)
#define DATA_PAYLOAD_ADDR   (DATA_ADDR + (sizeof(int)))

/* @brief
 * Initialize the flasher utility, including any
 * storage that will be needed for flashing
 */
int flasher_init(void);

/* @brief
 * Run the flasher utility with the given command
 */
int flasher_run(uint32_t command);
