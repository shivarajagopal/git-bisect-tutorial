import os
import sys

def update_firmware(filename):
    return run_flasher(filename)

def main():
    return flash(sys.argv[1])


if __name__ == "__main__":
    exit(main())
