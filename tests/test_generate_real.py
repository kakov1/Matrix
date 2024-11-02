from numpy import matrix, linalg, array, float64
from random import uniform
from functools import reduce
from decimal import *

getcontext().prec = 20

test_number_start = int(input("Input start test number:\n"))
test_number_stop = int(input("Input stop test number:\n"))

for i in range(test_number_start, test_number_stop + 1):
    matrix_ = array([[Decimal(uniform(1, 5)) for _ in range(10)] for __ in range(10)], dtype=float64)
    det = Decimal(linalg.det(matrix_))
        
    with open(f"./tests/{i}test.txt", "w") as test_file:
        test_file.write("10\n")
        for k in range(10):
            for j in range(10):
                test_file.write(f"{matrix_[k][j]:.20f} ")
            test_file.write("\n")
            
    with open(f"./tests/{i}answer.txt", "w") as answer_file:
        answer_file.write(f"{det}\n")
