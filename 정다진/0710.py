import sys

# 변수
# x와 y는 드래곤 커브의 시작 점, d는 시작 방향, g는 세대
# (0 ≤ x, y ≤ 100, 0 ≤ d ≤ 3, 0 ≤ g ≤ 10)


board = [[0]*101 for _ in range(101)]
# 진행방향 구하면 방향
# def coordinate(x,y,dir):

#     dx = [1, 0, -1, 0]
#     dy = [0, -1, 0, 1]
#     board[x][y] = 1

#     for i in dir:
#         x += dy[i]
#         y += dx[i]
#         board[x][y] =  1

ddir = [(0,1), (-1,0), (0,-1), (1,0)]



# 커브 함수
# 방향
# 0 -> 1
# 1 -> 2
# 2 -> 3
# 3 -> 0
def curve(d,g):
    dir = [d]
    for i in range(g):
        for j in range(len(dir)-1, -1, -1):
            dir.append((dir[j] + 1) % 4)

    return dir


# 세대
# 0세대 : 화살표 1개 2^0
# 1세대 : 화살표 2개 (1 + 1) 2^1
# 2세대 : 화살표 4개 (2 + 2) 2^2
# 3세대 : 화살표 8개 (4 + 4) 2^3
# => n세대 화살표 개수 : 2^n 개


# 커브 개수 입력
n = int(input())

for _ in range(n):
    x, y, d, g = map(int, input().split())

    var_1 = curve(d,g)
    board[x][y] =  1
    for var_1 in var_1:
        x += ddir[var_1][1]
        y += ddir[var_1][0]
        board[x][y] =  1


# 사각형 수
# for 문으로
# 4칸 좌표 = True
square = 0
for x in range(100):
    for y in range(100):
        if board[x][y] and board[x][y+1] and board[x+1][y] and board[x+1][y+1]:
            square += 1

# 출력
print(square)

