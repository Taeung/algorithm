#!/bin/python

input_file = open("input","r")
test_script = open("test.sh","w")

test_script.write("#!/bin/bash\n")
test_script.write("echo -e \"")
lines = input_file.readlines()

for line in lines:
    test_script.write(line[:-1]+"\\n\\\n")

test_script.write("\" | ./a.out")


