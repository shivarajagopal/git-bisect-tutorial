#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* @brief
 * Initialize the flasher utility, including any
 * storage that will be needed for flashing
 */
int flasher_init(void);

/* @brief
 * Run the flasher utility with the given command
 */
int flasher_run(uint32_t command);
