#!/bin/python
import random
import os
import platform

if platform.system() != 'Linux':
    print "Can't generate test script on OS other than Linux"
    exit()

def get_gcc_version():
    return os.popen('gcc --version').readline().rstrip()

def get_gcc_options():
    dirname = os.path.split(os.getcwd())[1]
    filename = dirname + ".c"
    return "gcc -ggdb " + filename + " -ansi -fno-asm -O2 -Wall -lm --static"

def get_os_info():
    return platform.platform()

def test_script__new():
    test_script = open("test.sh","w")
    test_script.write("#!/bin/bash\n")
    test_script.write("#\n# TEST ENVIRONMENT\n")
    test_script.write("# gcc version: " + get_gcc_version() + "\n")
    test_script.write("# gcc options: " + get_gcc_options() + "\n")
    test_script.write("# os: " + get_os_info() + "\n\n")
    return test_script

test_script = test_script__new()
test_script.write("echo -e \"")

nr = random.randrange(1,100000)
height = random.randrange(1,1000000000)
test_script.write(str(nr))

for i in range(1,nr):
    h = random.randrange(1,height)
    test_script.write(" "+str(h))

test_script.write("\" | ./$1")
