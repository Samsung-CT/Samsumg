# visited 도입 요망
# 더 나은 로직 : 모든 구슬 이동 -> 위치 겹치는 경우 이동량을 파악 -> 위치 조정

from collections import deque


def check():
    if new_blue_x == -1 and new_red_x == -1:
        return False
    elif new_blue_x == -1 or new_blue_y == -1:
        return False
    elif new_red_x == -1 or new_red_y == -1:
        return True
    q.append([new_red_x, new_red_y, new_blue_x, new_blue_y, cnt])


def move(x, y, dx, dy, ox, oy):
    nx, ny = x, y
    while True:
        nx, ny = nx + dx, ny + dy
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            break
        if graph[nx][ny] == '#' or (nx == ox and ny == oy):
            return nx - dx, ny - dy
        elif graph[nx][ny] == 'O':
            return -1, -1


n, m = map(int, input().split())
graph = [list(map(str, input())) for _ in range(n)]
flag = True

for i in range(n):
    for j in range(m):
        if graph[i][j] == "R":
            red_x, red_y = i, j
            graph[i][j] = "."
        elif graph[i][j] == "B":
            blue_x, blue_y = i, j
            graph[i][j] = "."
        # '0'의 위

moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]

q = deque([[red_x, red_y, blue_x, blue_y, 0]])
while q:
    red_x, red_y, blue_x, blue_y, cnt = q.popleft()
    if cnt == 10:
        break
    else:
        cnt += 1

    if red_x > blue_x:
        new_blue_x, new_blue_y = move(blue_x, blue_y, -1, 0, red_x, red_y)
        new_red_x, new_red_y = move(red_x, red_y, -1, 0, new_blue_x, new_blue_y)
        if check():
            print(cnt)
            flag = False
            break

        new_red_x, new_red_y = move(red_x, red_y, 1, 0, blue_x, blue_y)
        new_blue_x, new_blue_y = move(blue_x, blue_y, 1, 0, new_red_x, new_red_y)
        if check():
            print(cnt)
            flag = False
            break
    else:
        new_red_x, new_red_y = move(red_x, red_y, -1, 0, blue_x, blue_y)
        new_blue_x, new_blue_y = move(blue_x, blue_y, -1, 0, new_red_x, new_red_y)
        if check():
            print(cnt)
            flag = False
            break

        new_blue_x, new_blue_y = move(blue_x, blue_y, 1, 0, red_x, red_y)
        new_red_x, new_red_y = move(red_x, red_y, 1, 0, new_blue_x, new_blue_y)
        if check():
            print(cnt)
            flag = False
            break

    if red_y > blue_y:
        new_blue_x, new_blue_y = move(blue_x, blue_y, 0, -1, red_x, red_y)
        new_red_x, new_red_y = move(red_x, red_y, 0, -1, new_blue_x, new_blue_y)
        if check():
            print(cnt)
            flag = False
            break

        new_red_x, new_red_y = move(red_x, red_y, 0, 1, blue_x, blue_y)
        new_blue_x, new_blue_y = move(blue_x, blue_y, 0, 1, new_red_x, new_red_y)
        if check():
            print(cnt)
            flag = False
            break
    else:
        new_red_x, new_red_y = move(red_x, red_y, 0, -1, blue_x, blue_y)
        new_blue_x, new_blue_y = move(blue_x, blue_y, 0, -1, new_red_x, new_red_y)
        if check():
            print(cnt)
            flag = False
            break

        new_blue_x, new_blue_y = move(blue_x, blue_y, 0, 1, red_x, red_y)
        new_red_x, new_red_y = move(red_x, red_y, 0, 1, new_blue_x, new_blue_y)
        if check():
            print(cnt)
            flag = False
            break

if flag:
    print(-1)
