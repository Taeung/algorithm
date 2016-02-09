#!/bin/python
import random

test_script = open("test.sh","w")
test_script.write("#!/bin/bash\n")
test_script.write("echo -e \"")

nr_col = random.randrange(3, 101)
nr_row = random.randrange(3, 101)

test_script.write(str(nr_col) + " " + str(nr_row) + "\\n\\\n")

def write_zero_line(nr_row):
    row = ""
    for i in range(0, nr_row):
        row += "0"
    test_script.write(row)

write_zero_line(nr_row)
test_script.write("\\n\\\n")
nr_inner_col = nr_col - 2
nr_inner_row = nr_row - 2

for i in range(0, nr_inner_col):
    test_script.write("0")
    for i in range(0, nr_inner_row):
        cheese_cell = random.randrange(0, 2)
        test_script.write(str(cheese_cell))
    test_script.write("0\\n\\\n")

write_zero_line(nr_row)
test_script.write("\\n\" | ./$1")
