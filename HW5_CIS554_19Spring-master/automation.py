import copyFunction
import os
# import time



import sys
import time
import subprocess

def main():
    files = os.listdir("Student1/")

    for file in files:
        copyFunction.copyFunction(file, False)
        os.system("run.bat")
        print(file)
        input("Press Enter to continue...")

# def main():
#     copyFunction.copyFunction(sys.argv[1])
#     subprocess.call("run.bat", shell=True)


if __name__ == "__main__":
    main()