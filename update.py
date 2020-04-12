import os
import sys
import debugger

# Memory Map
COMMAND_ADDR = 0x10101000
COMMAND_RET_CODE_ADDR = 0x10101004
DATA_SECTOR_ADDR = 0x10102000
DATA_ADDR = 0x10110000
DATA_SIZE_ADDR = DATA_ADDR
DATA_PAYLOAD_ADDR = DATA_ADDR + 4

# Commands
FORMAT = 0x0
WRITE = 0x1
READ = 0x2
VERIFY = 0x3

def debugger_memory_read(addr, size):
    return debugger.read(addr, size)

def debugger_memory_write(addr, data, size):
    return debugger.write(addr, data, size)

def get_return_code():
    debugger_memory_read(COMMAND_RET_CODE_ADDR, 4)

def format_memory():
    debugger_memory_write(COMMAND_ADDR, FORMAT)

def write_memory(data, sector):
    debugger_memory_write(DATA_SECTOR_ADDR, sector)
    debugger_memory_write(DATA_SIZE_ADDR, len(data))
    debugger_memory_write(DATA_PAYLOAD_ADDR, data)
    debugger_memory_write(COMMAND_ADDR, WRITE)

def read_memory(sector, size):
    debugger_memory_write(DATA_SECTOR_ADDR, sector)
    debugger_memory_write(DATA_SIZE_ADDR, size)
    debugger_memory_write(COMMAND_ADDR, READ)
    data = debugger_memory_read(DATA_PAYLOAD_ADDR, size)
    return data

def verify_memory(sector, data):
    debugger_memory_write(DATA_SECTOR_ADDR, sector)
    debugger_memory_write(DATA_SIZE_ADDR, len(data))
    debugger_memory_write(DATA_PAYLOAD_ADDR, data)
    debugger_memory_write(COMMAND_ADDR, VERIFY)

def load_and_run_flasher():
    debugger.load("path to flasher binary")
    debugger.run()

def update_firmware(filename):
    # Load up and kick off the flasher
    load_and_run_flasher()

    # Format the chip
    format_memory()
    format_ret_code = get_return_code()
    assert(format_ret_code == 0)

    # Read in the file to flash
    file_data = ''
    with open(filename) as f:
        file_data = f.read()

    # Write the memory with the file data
    write_memory(0, file_data)
    write_ret_code = get_return_code()
    assert(write_ret_code = get_return_code())

    # Verify the data from flash
    verify_ret_code = verify_memory(0, file_data)
    assert(verify_ret_code = get_return_code())

def main():
    return update_firmware(sys.argv[1])

if __name__ == "__main__":
    exit(main())
