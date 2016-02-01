#!/bin/python
import random

test_script = open("test.sh","w")

test_script.write("#!/bin/bash\n")
test_script.write("echo -e \"")

nr = random.randrange(1, 50001)
order = random.randrange(0, 2)

test_script.write(str(nr)+"\\n\\\n")
test_script.write(str(order)+"\\n\\\n")

billion = 10 ** 9
for i in range(1,nr):
    num = random.randrange(0, billion)
    test_script.write(str(num)+"\\n\\\n")

num = random.randrange(1, billion)
test_script.write(str(num)+"\\n\" | ./$1")
