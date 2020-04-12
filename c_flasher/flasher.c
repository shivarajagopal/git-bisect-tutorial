#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

#include "flasher.h"

#include "flash_memory.h"

/* @brief
 * Initialize the flasher utility, including any
 * storage that will be needed for flashing
 */
int flasher_init(void)
{
  printf("Initialize flash storage...");
  return 0;
}

int flasher_format(void)
{
  printf("Formatting flash storage...");
  memset((void *) FLASH_MEM_START_ADDR, 0, FLASH_TOTAL_SIZE);
  return 0;
}

int flasher_write(void)
{
  return 0;
}

int flasher_read(void)
{
  return 0;
}

int flasher_verify(void)
{
  return 0;
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
      flasher_format();
      break;
    case memory_write:
      flasher_write();
      break;
    case memory_read:
      flasher_read();
      break;
    case memory_verify:
      flasher_verify();
      break;
    default:
      assert(false);
  }
  return 0;
}
