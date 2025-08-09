# debug_gui/app.py

import tkinter as tk
from tkinter import ttk
import threading
import os
import subprocess
from pathlib import Path
import queue
import time
import re


class GDBMIProcess:
    def __init__(self, gdb_path="gdb-multiarch"):
        self.proc = subprocess.Popen(
            [gdb_path, "--interpreter=mi2"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
            bufsize=1
        )
        self.stdout_queue = queue.Queue()
        self._start_reader()

    def _start_reader(self):
        def read_stdout():
            while True:
                line = self.proc.stdout.readline()
                if not line:
                    break
                self.stdout_queue.put(line.strip())

        threading.Thread(target=read_stdout, daemon=True).start()

    def write(self, command: str):
        if self.proc.stdin:
            self.proc.stdin.write(command + "\n")
            self.proc.stdin.flush()

    def get_responses(self, timeout=0.1):
        responses = []
        start_time = time.time()
        while time.time() - start_time < timeout:
            try:
                line = self.stdout_queue.get(timeout=timeout)
                responses.append(line)
            except queue.Empty:
                break
        return responses

    def close(self):
        if self.proc.stdin:
            self.proc.stdin.write("quit\n")
            self.proc.stdin.flush()
        self.proc.terminate()


class DebuggerApp(tk.Tk):
    def __init__(self, bootloader_elf, port):
        super().__init__()
        self.title("GDB Debugger GUI")
        self.geometry("1200x1000")

        self.gdb = GDBMIProcess()
        self.setup_ui()
        self.listen_gdb()

        # Init GDB session
        self.send_gdb("file " + str(bootloader_elf))
        self.send_gdb(f"target remote localhost:{port}")
        self.send_gdb("list")
        self.send_gdb("bt")

    def setup_ui(self):
        self.columnconfigure(1, weight=1)
        self.rowconfigure(0, weight=1)

        self.tree = ttk.Treeview(self)
        self.tree.grid(row=0, column=0, sticky="ns")
        self.populate_file_tree(Path("."))

        self.notebook = ttk.Notebook(self)
        self.notebook.grid(row=0, column=1, sticky="nsew")
        self.editors = {}

        # GDB Output Console (bottom)
        self.console_frame = ttk.Frame(self)
        self.console_frame.grid(row=1, column=0, columnspan=2, sticky="nsew")
        self.rowconfigure(1, weight=0)

        self.console_text = tk.Text(self.console_frame, height=15, wrap="none", state="disabled", bg="#111", fg="#0f0")
        self.console_text.pack(side="left", fill="x", expand=True)

        scrollbar = ttk.Scrollbar(self.console_frame, command=self.console_text.yview)
        scrollbar.pack(side="right", fill="y")
        self.console_text.config(yscrollcommand=scrollbar.set)

        # Buttons
        btns = ttk.Frame(self)
        btns.grid(row=2, column=0, columnspan=2)
        for name in ["next", "step", "stepi", "continue", "return", "backtrace"]:
            ttk.Button(btns, text=name, command=lambda n=name: self.send_gdb(n)).pack(side="left")

    def populate_file_tree(self, path):
        for item in os.listdir(path):
            full = path / item
            self.tree.insert('', 'end', text=item)

    def open_file(self, filepath):
        if filepath in self.editors:
            self.notebook.select(self.editors[filepath])
            return

        # Make the text editor with normal colors
        text = tk.Text(
            self.notebook,
            bg="white",       # Or "#1e1e1e" for dark theme
            fg="black",       # Or "#ffffff" for dark theme
            insertbackground="black",  # Cursor color
            wrap="none"
        )

        try:
            with open(filepath) as f:
                text.insert("1.0", f.read())
        except Exception as e:
            text.insert("1.0", f"[Error reading file: {filepath}]\n{e}")

        # Make sure editor is editable
        text.config(state="normal")

        tab = ttk.Frame(self.notebook)
        text.pack(expand=True, fill="both", in_=tab)
        self.notebook.add(tab, text=os.path.basename(filepath))
        self.editors[filepath] = tab
        self.current_editor = text


    def send_gdb(self, cmd):
        self.print_console(f">>> {cmd}")
        self.gdb.write(cmd)

    def listen_gdb(self):
        def loop():
            while True:
                responses = self.gdb.get_responses(timeout=0.5)
                for line in responses:
                    self.print_console(line)
                    if "frame={" in line:
                        fullname = self._extract_value(line, "fullname")
                        line_no = self._extract_value(line, "line")                       
                        if fullname and line_no:
                            try:
                                self.open_file(fullname)
                                self.highlight_line(fullname, int(line_no))
                            except Exception:
                                pass
        threading.Thread(target=loop, daemon=True).start()

    def print_console(self, msg):
        self.console_text.config(state="normal")
        self.console_text.insert("end", msg + "\n")
        self.console_text.see("end")
        self.console_text.config(state="disabled")

    def _extract_value(self, text, key):
        match = re.search(rf'{key}="([^"]+)"', text)
        return match.group(1) if match else None

    def highlight_line(self, file, line):
        editor = self.current_editor
        editor.tag_remove("highlight", "1.0", "end")
        editor.tag_add("highlight", f"{line}.0", f"{line}.end")
        editor.tag_config("highlight", background="yellow")
        editor.see(f"{line}.0")

