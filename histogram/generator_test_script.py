#!/bin/python
import random

test_script = open("test.sh","w")

test_script.write("#!/bin/bash\n")
test_script.write("echo -e \"")

nr = random.randrange(1,100000)
height = random.randrange(1,1000000000)
test_script.write(str(nr))

for i in range(1,nr):
    h = random.randrange(1,height)
    test_script.write(" "+str(h))

test_script.write("\" | ./$1")
