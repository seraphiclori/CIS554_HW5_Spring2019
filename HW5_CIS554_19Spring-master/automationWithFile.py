import subprocess
import copyFunction
import sys

def main():
    copyFunction.copyFunction(sys.argv[1], True)
    subprocess.call("run.bat", shell=True)

if __name__ == "__main__":
    main()