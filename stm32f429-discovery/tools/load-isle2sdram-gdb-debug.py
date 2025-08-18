#!/usr/bin/env python3

import sys
import subprocess
import time
import shutil
from pathlib import Path
from gdb_gui_tkinter.debug_gui import DebuggerApp
import socket
import os

if len(sys.argv) != 3:
    print("Usage: python3 load-isle2sdram-gdb-debug.py <path_to_isle_dir> <path_to_bootloader>")
    sys.exit(1)

def get_free_port():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(('', 0))  # Bind to a free port assigned by the OS
        return s.getsockname()[1]

# Align down to 4-byte boundary
def align_down(addr, alignment):
    return addr & ~(alignment - 1)

PORT = get_free_port()

ISLE_DIR = Path(sys.argv[1]).resolve()
BOOTLOADER_PATH = Path(sys.argv[2]).resolve()

ISLE_ELF = ISLE_DIR / "isle"
ISLE_BIN = ISLE_DIR / "isle.bin"
ISLE_BIN_GZ = ISLE_DIR / "isle.bin.gz"
BOOTLOADER_ELF = BOOTLOADER_PATH / "bootloader-in-flash.elf"
SDRAM_ADDR = 0x90000000
SDRAM_SIZE = 8 * 1024 * 1024

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
check_file(ISLE_BIN_GZ)
check_file(BOOTLOADER_ELF)
check_tool(STLINK_GDBSERVER)
check_tool(STM32_PROG_CLI)
check_tool("gdb-multiarch")

base_dir = os.path.dirname(os.path.abspath(__file__))
project_path = os.path.abspath(os.path.join(base_dir, "..", ".."))

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
gdbserver_proc = subprocess.Popen(
    [
        str(STLINK_GDBSERVER),
        "-cp", str(Path(STM32_PROG_CLI).parent),
        "-p", f"{PORT}",
        "-l", "1",
        "-d",
        "-s",
        "-m", "0",
        "-k",
        "--halt",
        "-e"
    ],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
    bufsize=1
)

# Wait for ready message
LineFound = False
for line in iter(gdbserver_proc.stdout.readline, ''):
    print(line, end="")  # optional: live print
    if "Waiting for debugger connection..." in line:
        LineFound = True
        break
if not LineFound:
    os.exit(1)
del LineFound

# Compute compressed binary size
isle_gz_size = ISLE_BIN_GZ.stat().st_size

# Compute destination address in SDRAM
isle_gz_dest_addr = align_down(SDRAM_ADDR + SDRAM_SIZE - isle_gz_size - 8, 4)

if True:
    print(f"[*] Loading {ISLE_BIN_GZ} to SDRAM at address 0x{isle_gz_dest_addr:X}")
    try:
        subprocess.run([
            "gdb-multiarch",
            str(BOOTLOADER_ELF),
            "-ex", "set confirm off",
            "-ex", "set pagination off",
            "-ex", f"target remote localhost:{PORT}",

            "-ex", "tbreak main",
            "-ex", "continue",
            "-ex", "list",
            "-ex", "bt",
            
            "-ex", "p SystemCoreClock", # 16MHz?

            "-ex", "tbreak decompress_sdram_code",
            "-ex", "continue",
            "-ex", "list",
            "-ex", f"set isle_gz_start_address=0x{isle_gz_dest_addr:X}",
            "-ex", f"set isle_gz_size={isle_gz_size}",
            "-ex", f"restore {ISLE_BIN_GZ} binary 0x{isle_gz_dest_addr:X}",

            "-ex", "tbreak execute_sdram_code_from_ivt",
            "-ex", "continue",
            "-ex", "list",
#           "-ex", f"restore {ISLE_BIN} binary 0x{SDRAM_ADDR:X}",
            "-ex", f"add-symbol-file {ISLE_ELF} 0x{SDRAM_ADDR:X}",

            "-ex", "tbreak SDL_AppInit",
            "-ex", "continue",
            "-ex", "list",
             
             "-ex", "quit"
        ])
        
        print("[*] Testing target attach...")
        
        subprocess.run([
            "gdb-multiarch",
            str(ISLE_ELF),
            "-ex", "set confirm off",
            "-ex", "set pagination off",
            "-ex", f"target remote localhost:{PORT}",
            
            "-ex", "list",
            "-ex", "bt",
            
            "-ex", "quit"
        ])
        
        print("[*] Launching GUI debugger...")
        
        app = DebuggerApp(
            f"{ISLE_ELF}",
            project_dir=project_path,
            gdb_path="gdb-multiarch",
            extra_init_cmds=[f"target remote localhost:{PORT}"]
        )
        app.mainloop()    
    except KeyboardInterrupt:
        print("\n[*] Ctrl+C received.")
else:
    print("[*] Debugging Bootlaoder only")
    try:
        subprocess.run([
            "gdb-multiarch",
            str(BOOTLOADER_ELF),
            "-ex", "set confirm off",
            "-ex", "set pagination off",
            "-ex", f"target remote localhost:{PORT}",

            "-ex", "tbreak main",
            "-ex", "continue",
            "-ex", "list",
            "-ex", "bt",
             
             "-ex", "quit"
        ])
        
        print("[*] Testing target attach...")
        
        subprocess.run([
            "gdb-multiarch",
            str(BOOTLOADER_ELF),
            "-ex", "set confirm off",
            "-ex", "set pagination off",
            "-ex", f"target remote localhost:{PORT}",
            
            "-ex", "list",
            "-ex", "bt",
            
            "-ex", "quit"
        ])
        
        print("[*] Launching GUI debugger...")

        app = DebuggerApp(
            f"{BOOTLOADER_ELF}",
            project_dir=project_path,
            gdb_path="gdb-multiarch",
            extra_init_cmds=[f"target remote localhost:{PORT}"]
        )
        app.mainloop()    
    except KeyboardInterrupt:
        print("\n[*] Ctrl+C received.")    

print("[*] Stopping ST-LINK_gdbserver...")
gdbserver_proc.terminate()
gdbserver_proc.wait()

print("[*] Resetting terminal...")
subprocess.run(["stty", "sane"])
subprocess.run(["reset"], stdin=sys.__stdin__, stdout=sys.__stdout__, stderr=sys.__stderr__)

print("[*] Done.")

