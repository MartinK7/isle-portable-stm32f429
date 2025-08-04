#!/usr/bin/env python3

import sys
import subprocess
import time
import shutil
from pathlib import Path
from pygdbmi.gdbcontroller import GdbController

if len(sys.argv) != 3:
    print("Usage: python3 load-isle2sdram-gdb-debug.py <path_to_isle_dir> <path_to_bootloader>")
    sys.exit(1)

ISLE_DIR = Path(sys.argv[1]).resolve()
BOOTLOADER_PATH = Path(sys.argv[2]).resolve()

ISLE_ELF = ISLE_DIR / "isle"
ISLE_BIN = ISLE_DIR / "isle.bin"
BOOTLOADER_ELF = BOOTLOADER_PATH / "bootloader-in-flash.elf"
SDRAM_ADDR = "0x90000000"

STLINK_GDBSERVER = Path("ST-LINK_gdbserver")
STM32_PROG_CLI = shutil.which("STM32_Programmer_CLI")

# Sanity checks
def check_file(path: Path):
    if not path.is_file():
        print(f"Missing file: {path}")
        sys.exit(1)

def check_tool(name_or_path):
    if not shutil.which(name_or_path):
        print(f"Missing tool: {name_or_path}")
        sys.exit(1)

check_file(ISLE_ELF)
check_file(ISLE_BIN)
check_file(BOOTLOADER_ELF)
check_tool(STLINK_GDBSERVER)
check_tool(STM32_PROG_CLI)
check_tool("gdb-multiarch")

# Flash ELF using STM32_Programmer_CLI with halt
print(f"[*] Flashing {BOOTLOADER_ELF} using {STM32_PROG_CLI}...")
flash_cmd = [
    STM32_PROG_CLI,
    "-c", "port=SWD",
    "-w", str(BOOTLOADER_ELF),
    "-v",  # verify after write
    "-halt"
]
subprocess.run(flash_cmd, check=True)

print("[*] Starting ST-LINK_gdbserver...")
gdbserver_proc = subprocess.Popen([
    str(STLINK_GDBSERVER),
    "-cp", str(Path(STM32_PROG_CLI).parent),
    "-p", "61222",
    "-l", "1",
    "-d",
    "-s",
    "-m", "0",
    "-k"
], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

time.sleep(1)  # wait for gdbserver to be ready

print("[*] Launching gdb-multiarch in TUI mode for manual debug...")
try:
    subprocess.run([
        "gdb-multiarch",
        str(BOOTLOADER_ELF),
        "-ex", "set confirm off",
        "-ex", "target remote localhost:61222",

        "-ex", "tbreak main",
        "-ex", "continue",
        "-ex", "list",

        "-ex", "tbreak execute_sdram_code_from_ivt",
        "-ex", "continue",
        "-ex", "list",

        "-ex", f"restore {ISLE_BIN} binary {SDRAM_ADDR}",
        "-ex", f"add-symbol-file {ISLE_ELF} {SDRAM_ADDR}",

        "-ex", "tbreak SDL_AppInit",
        "-ex", "continue",
        "-ex", "list",
        
#        "-ex", "quit",

#        "-ex", "tui enable",
#        "-ex", "layout src",
#        "-ex", "layout regs",
#        "-ex", "focus cmd"
    ])
except KeyboardInterrupt:
    print("\n[*] Ctrl+C received.")

print("[*] Stopping ST-LINK_gdbserver...")
gdbserver_proc.terminate()
gdbserver_proc.wait()

print("[*] Resetting terminal...")
subprocess.run(["stty", "sane"])
subprocess.run(["reset"], stdin=sys.__stdin__, stdout=sys.__stdout__, stderr=sys.__stderr__)

print("[*] Done.")

