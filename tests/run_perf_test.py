import subprocess
import sys
import os

# Get the script directory
script_dir = os.path.dirname(os.path.abspath(__file__))
os.chdir(script_dir)

print(f"Working directory: {os.getcwd()}")

result = subprocess.run(["nasm", "-f", "win64", "../src/asm/converter.asm", "-o", "converter.obj"])
if result.returncode != 0:
    sys.exit(1)

result = subprocess.run(["gcc", "-I", "../src/c", "comp_perf_test.c", "converter.obj", "-o", "comp_perf_test.exe"])
if result.returncode != 0:
    sys.exit(1)

result = subprocess.run(["comp_perf_test.exe"])

# Cleanup
try:
    os.remove("converter.obj")
    os.remove("comp_perf_test.exe")
except:
    pass

sys.exit(result.returncode)
