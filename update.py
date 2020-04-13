import os
import sys
import debugger_probe

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

class Debugger():
    probe = None

    def __init__(self):
        self.probe= debugger_probe.Probe()

    def load(self, filename);
        return self.probe.load(filename)

    def run(self):
        return self.probe.run()

    def memory_read(self, addr, size):
        return self.probe.read(addr, size)

    def memory_write(self, addr, data, size):
        return self.probe.write(addr, data, size)

class MemInterface():
    debugger = None

    def __init__(self):
        self.debugger = Debugger()

    # Read back the return code
    def get_return_code(self):
        self.debugger.memory_read(COMMAND_RET_CODE_ADDR, 4)

    # Format the memory block
    def format_memory(self):
        self.debugger.memory_write(COMMAND_ADDR, FORMAT)

    # Write a set of data to a given sector
    def write_memory(self, data, sector):
        self.debugger.memory_write(DATA_SECTOR_ADDR, sector)
        self.debugger.memory_write(DATA_SIZE_ADDR, len(data))
        self.debugger.memory_write(DATA_PAYLOAD_ADDR, data)
        self.debugger.memory_write(COMMAND_ADDR, WRITE)

    # Read a given length of data starting at a given sector
    def read_memory(self, sector, size):
        self.debugger.memory_write(DATA_SECTOR_ADDR, sector)
        self.debugger.memory_write(DATA_SIZE_ADDR, size)
        self.debugger.memory_write(COMMAND_ADDR, READ)
        data = self.debugger.memory_read(DATA_PAYLOAD_ADDR, size)
        return data

    # Verify that the given data matches the data at the given sector on chip
    def verify_memory(self, sector, data):
        self.debugger.memory_write(DATA_SECTOR_ADDR, sector)
        self.debugger.memory_write(DATA_SIZE_ADDR, len(data))
        self.debugger.memory_write(DATA_PAYLOAD_ADDR, data)
        self.debugger.memory_write(COMMAND_ADDR, VERIFY)

    # Load flasher binary into chip using debugger probe and run
    def load_and_run_flasher(self, flasher_binary):
        self.debugger.load("path to flasher binary")
        self.debugger.run()

def update_firmware(mem_interface, filename):
    # Load up and kick off the flasher
    mem_interface.load_and_run_flasher()

    # Format the chip
    mem_interface.format_memory()
    format_ret_code = mem_interface.get_return_code()
    assert(format_ret_code == 0)

    # Read in the file to flash
    file_data = ''
    with open(filename) as f:
        file_data = f.read()

    # Write the memory with the file data
    mem_interface.write_memory(0, file_data)
    write_ret_code = mem_interface.get_return_code()
    assert(write_ret_code == 0)

    # Verify the data from flash
    mem_interface.verify_memory(0, file_data)
    verify_ret_code = mem_interface.get_return_code()
    assert(verify_ret_code == 0)

def main():
    mem_interface = MemInterface()
    return update_firmware(mem_interface, sys.argv[1])

if __name__ == "__main__":
    exit(main())
