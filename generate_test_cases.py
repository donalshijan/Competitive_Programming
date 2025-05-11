import subprocess
import random
import os
import tempfile
import argparse

COMPLEXITY_LIMITS = {
    "O(n)": 1000,
    "O(n^2)": 100,
    "O(2^n)": 16,
    "O(n!)": 13
}

def generate_test_case(n, val_range=(1, 1000)):
    return [random.randint(*val_range) for _ in range(n)]

def run_cpp_solution(exe_path, test_input):
    try:
        result = subprocess.run(
            [exe_path],
            input=test_input.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=5
        )
        return result.stdout.decode().strip()
    except subprocess.TimeoutExpired:
        return "TIMEOUT"

def compile_cpp(source_path):
    exe_path = tempfile.mktemp()
    compile_result = subprocess.run(["g++", "-O2", source_path, "-o", exe_path])
    if compile_result.returncode != 0:
        raise RuntimeError("Compilation failed.")
    return exe_path

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("cpp_file", help="Path to brute-force C++ solution")
    parser.add_argument("complexity", choices=COMPLEXITY_LIMITS.keys())
    parser.add_argument("--tests", type=int, default=10)
    parser.add_argument("--minval", type=int, default=1)
    parser.add_argument("--maxval", type=int, default=1000)
    args = parser.parse_args()

    max_n = COMPLEXITY_LIMITS[args.complexity]
    exe_path = compile_cpp(args.cpp_file)

    for i in range(args.tests):
        n = random.randint(1, max_n)
        test_case = generate_test_case(n, (args.minval, args.maxval))
        test_input = f"{n}\n{' '.join(map(str, test_case))}\n"
        output = run_cpp_solution(exe_path, test_input)
        print("Input:")
        print(test_input.strip())
        print("Output:")
        print(output)
        print("="*30)

    os.remove(exe_path)

if __name__ == "__main__":
    main()
