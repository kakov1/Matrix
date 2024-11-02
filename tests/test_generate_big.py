from numpy import matrix, linalg, array
from random import randint
from functools import reduce

test_number_start = int(input("Input start test number:\n"))
test_number_stop = int(input("Input stop test number:\n"))

for i in range(test_number_start, test_number_stop + 1):
    numbers = [randint(1, 20) for _ in range(1, 101)]

    check = []
    for _ in range(90):
        pos = randint(0, 99)
        while (pos in check):
            pos = randint(0, 99)
        check.append(pos)
        numbers[pos] = 1
    
    matrix_ = array([[0 for _ in range(100)] for __ in range(100)])
    det = reduce(lambda a, b: a * b, numbers)

    for k in range(100):
        for j in range(100):
            if k == j:
                matrix_[k][j] =  numbers[k]
            elif j > k:
                matrix_[k][j] = randint(0, 100)

    for _ in range(100):
        num1 = randint(0, 99)
        num2 = randint(0, 99)
        while num1 == num2:
            num1 = randint(0, 99)
        matrix_[num1] += matrix_[num2]
        
    with open(f"./tests/{i}test.txt", "w") as test_file:
        test_file.write("100\n")
        for k in range(100):
            for j in range(100):
                test_file.write(f"{matrix_[k][j]} ")
            test_file.write("\n")
            
    with open(f"./tests/{i}answer.txt", "w") as answer_file:
        answer_file.write(f"{det}\n")
