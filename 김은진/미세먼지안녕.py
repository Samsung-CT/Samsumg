from collections import deque


def spread(board):
    new_board = [[0] * c for _ in range(r)]

    q = deque()
    for i in range(r):
        for j in range(c):
            if board[i][j] >= 5:
                q.append([i, j, board[i][j]])
            else:
                new_board[i][j] = board[i][j]

    while q:
        x, y, z = q.popleft()
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if nx < 0 or nx >= r or ny < 0 or ny >= c:
                continue
            elif new_board[nx][ny] == -1:
                continue

            new_board[nx][ny] += board[x][y]//5
            z -= board[x][y]//5

        new_board[x][y] += z

    return new_board


def air_cleaner_top():
    backup = graph[cleaner][1]
    graph[cleaner][1] = 0

    for y in range(2, c):
        graph[cleaner][y], backup = backup, graph[cleaner][y]
    for x in range(cleaner - 1, 0, -1):
        graph[x][c - 1], backup = backup, graph[x][c - 1]
    for y in range(c - 1, -1, -1):
        graph[0][y], backup = backup, graph[0][y]
    for x in range(1, cleaner):
        graph[x][0], backup = backup, graph[x][0]

    return


def air_cleaner_bottom():
    backup = graph[cleaner+1][1]
    graph[cleaner + 1][1] = 0

    for y in range(2, c):
        graph[cleaner+1][y], backup = backup, graph[cleaner+1][y]
    for x in range(cleaner+2, r-1):
        graph[x][c-1], backup = backup, graph[x][c-1]
    for y in range(c-1, -1, -1):
        graph[r-1][y], backup = backup, graph[r-1][y]
    for x in range(r-2, cleaner+1, -1):
        graph[x][0], backup = backup, graph[x][0]

    return



r, c, t = map(int, input().split())
graph = [list(map(int, input().split())) for _ in range(r)]

for i in range(2, r):
    if graph[i][0] == -1:
        cleaner = i
        break



for _ in range(t):
    graph = spread(graph)
    air_cleaner_bottom()
    air_cleaner_top()

ans = 2
for i in range(r):
    ans += sum(graph[i])

print(ans)




