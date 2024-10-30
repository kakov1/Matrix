from numpy import matrix, linalg, array
from random import randint
from functools import reduce

numbers = [randint(1, 20) for _ in range(1, 101)]

check = []
for i in range(90):
    pos = randint(0, 99)
    while (pos in check):
        pos = randint(0, 99)
    check.append(pos)
    numbers[pos] = 1
    
matrix_ = array([[0 for i in range(100)] for j in range(100)])
det = reduce(lambda a, b: a * b, numbers)

for i in range(100):
    for j in range(100):
        if i == j:
            matrix_[i][j] =  numbers[i]
        elif j > i:
            matrix_[i][j] = randint(0, 100)

for i in range(100):
    num1 = randint(0, 99)
    num2 = randint(0, 99)
    while num1 == num2:
        num1 = randint(0, 99)
    matrix_[num1] += matrix_[num2]

test_number = int(input("Input test number:\n"))
with open(f"./tests/{test_number}test.txt", "w") as test_file:
    test_file.write("100\n")
    for i in range(100):
        for j in range(100):
            test_file.write(f"{matrix_[i][j]} ")
        test_file.write("\n")
        
with open(f"./tests/{test_number}answer.txt", "w") as answer_file:
    answer_file.write(f"{det}\n")
