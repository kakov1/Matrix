from numpy import matrix, linalg, array
from random import randint
from functools import reduce

test_number_start = int(input("Input start test number:\n"))
test_number_stop = int(input("Input stop test number:\n"))

size = int(input("Input matrix size:\n"))

for i in range(test_number_start, test_number_stop + 1):
    numbers = [randint(1, 5) for _ in range(size)]

    check = []
    for _ in range(size - 10):
        pos = randint(0, size - 1)
        while (pos in check):
            pos = randint(0, size - 1)
        check.append(pos)
        numbers[pos] = 1
    
    matrix_ = array([[0 for _ in range(size)] for __ in range(size)])
    det = reduce(lambda a, b: a * b, numbers)

    for k in range(size):
        for j in range(size):
            if k == j:
                matrix_[k][j] =  numbers[k]
            elif j > k:
                matrix_[k][j] = randint(0, 10)

    for _ in range(size):
        num1 = randint(0, size - 1)
        num2 = randint(0, size - 1)
        while num1 == num2:
            num1 = randint(0, size - 1)
        matrix_[num1] += matrix_[num2]
        
    with open(f"./tests/{i}test.txt", "w") as test_file:
        test_file.write(f"{size}\n")
        for k in range(size):
            for j in range(size):
                test_file.write(f"{matrix_[k][j]} ")
            test_file.write("\n")
            
    with open(f"./tests/{i}answer.txt", "w") as answer_file:
        answer_file.write(f"{det}\n")
