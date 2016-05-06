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
nr_col = random.randrange(3, 101)
nr_row = random.randrange(3, 101)

test_script.write(str(nr_row) + " " + str(nr_col) + "\\n\\\n")

def write_zero_line(nr_col):
    row = ""
    for i in range(0, nr_col):
        row += "0 "
    test_script.write(row)

write_zero_line(nr_col-1)
test_script.write("0\\n\\\n")
nr_inner_row = nr_row - 2
nr_inner_col = nr_col - 2

for i in range(0, nr_inner_row):
    test_script.write("0 ")
    for i in range(0, nr_inner_col):
        cheese_cell = random.randrange(0, 2)
        test_script.write(str(cheese_cell) + " ")
    test_script.write("0\\n\\\n")

write_zero_line(nr_col-1)
test_script.write("0\\n\" | ./$1")
