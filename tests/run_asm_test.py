import subprocess
import sys
import os

# Change to script directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# nasm -f win64 converter.asm -o converter.obj
subprocess.run(["nasm", "-f", "win64", "    ", "-o", "converter.obj"])

subprocess.run(["gcc", "-I", "../src/c", "asm_test.c", "converter.obj", "-o", "asm_test.exe"])
result = subprocess.run(["./asm_test.exe"])
sys.exit(result.returncode)
