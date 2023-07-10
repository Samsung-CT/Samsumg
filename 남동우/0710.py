from sys import stdin

def rotate_x_y(input_x, input_y):
    return -1 * input_y, input_x

def get_first_direction(direction):
    if direction == 0:
        return 1, 0
    if direction == 1:
        return 0, -1
    if direction == 2:
        return -1, 0
    if direction == 3:
        return 0, 1

def make_dragon_curve(direction, goal_generation):
    # 무조건 시계 방향으로 90도 회전해, 그 다음 선분을 잇는다.
    first_x, first_y = get_first_direction(direction)
    current_generation = 0
    add_list = [(first_x, first_y)]

    while current_generation < goal_generation:
        compute_list = add_list[::-1]
        for element in compute_list:
            compute_x, compute_y = element
            rotating_x, rotating_y = rotate_x_y(-1 * compute_x, -1 * compute_y)
            add_list.append((rotating_x, rotating_y))

        current_generation += 1

    return add_list

def draw_on_matrix(matrix, start_x, start_y, curve_list):
    x, y = start_x, start_y
    matrix[y][x] = 1
    for element in curve_list:
        move_x, move_y = element
        x, y = x + move_x, y + move_y
        matrix[y][x] = 1

def check_on_left_up(matrix, x, y):
    return matrix[y][x] == matrix[y+1][x] == matrix[y][x+1] == matrix[y+1][x+1] == 1

n = int(stdin.readline())
matrix = [[0 for _ in range(101)] for _ in range(101)]

for i in range(n):
    x, y, d, g = map(int, stdin.readline().split())
    total_list = []
    dragon_curve_list = make_dragon_curve(d, g)
    draw_on_matrix(matrix, x, y, dragon_curve_list)

count = 0

for y in range(100):
    for x in range(100):
        if check_on_left_up(matrix, x, y):
            count += 1
print(count)
