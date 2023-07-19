from sys import stdin
from copy import deepcopy

height, width = map(int, stdin.readline().split())
matrix = [list(stdin.readline().rstrip()) for _ in range(height)]

direct = ((1, 0), (0, 1), (-1, 0), (0, -1))
direct_range = [(range(width - 2, 0, -1), range(height - 1)), (range(1, width), range(height - 2, 0, -1)),
                (range(1, width - 1), range(1, height - 1)), (range(1, width - 1), range(1, height - 1))]
hole = set()
global case_min
case_min = 999

def roll_one_ball(input_matrix, x, y, to_x, to_y):
    can_roll = False
    if input_matrix[y][x] == "B" or input_matrix[y][x] == "R":
        while input_matrix[y + to_y][x + to_x] == ".":
            can_roll = True
            input_matrix[y][x], input_matrix[y + to_y][x + to_x] = input_matrix[y + to_y][x + to_x], input_matrix[y][x]
            y += to_y
            x += to_x
        if input_matrix[y + to_y][x + to_x] == "O":
            can_roll = True
            hole.add(input_matrix[y][x])
            input_matrix[y][x] = "."
    return can_roll

def can_roll_to_direction(input_matrix, direct_index):
    hole.clear()
    to_x, to_y = direct[direct_index]
    range_x, range_y = direct_range[direct_index]

    can_roll = False
    if direct_index % 2 == 0:
        for x in range_x:
            for y in range_y:
                can_roll = roll_one_ball(input_matrix, x, y, to_x, to_y) or can_roll
    else:
        for y in range_y:
            for x in range_x:
                can_roll = roll_one_ball(input_matrix, x, y, to_x, to_y) or can_roll

    return can_roll and "B" not in hole

def backtracking(input_matrix, count, prev_direct):
    global case_min
    if count == 10:
        return

    for i in range(4):
        if prev_direct >= 0 and i == ((prev_direct + 2) % 4):
            continue
        clone_matrix = deepcopy(input_matrix)
        if can_roll_to_direction(clone_matrix, i):
            if "R" in hole:
                case_min = min(case_min, count + 1)
                return
            if "B" not in hole:
                backtracking(clone_matrix, count + 1, i)

backtracking(matrix, 0, -1)
print(case_min if case_min <= 10 else -1)
