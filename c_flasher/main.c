#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "flasher.h"

#define NO_COMMAND_MAGIC 0xAA55AA55

volatile uint32_t * command_reg = (volatile uint32_t *)COMMAND_ADDR;

uint32_t get_command(void)
{
  return *(command_reg);
}

void set_command(int32_t val)
{
  *(command_reg) = val;
}

int main(int32_t argc, char **argv)
{
  printf("Initializing flasher\n");
  int init_return_code = flasher_init();

  assert(init_return_code == 0);

  printf("Waiting for command\n");
  uint32_t command = NO_COMMAND_MAGIC;
  while (true)
  {
    command = get_command();
    if (command != NO_COMMAND_MAGIC)
    {
      break;
    }
  }
  // Run the command
  int flasher_return_code = flasher_run(command);
  // Set the return code into the return code memory location
  *(volatile int*) COMMAND_RET_CODE_ADDR = flasher_return_code;
  // Reset the command register
  set_command(NO_COMMAND_MAGIC);
  return 0;
}

    
