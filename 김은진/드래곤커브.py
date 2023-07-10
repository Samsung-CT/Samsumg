direct = [(0, 1), (-1, 0), (0, -1), (1, 0)]

n = int(input())
graph = [[0]*101 for _ in range(101)]

for _ in range(n):
    y, x, d, g = map(int, input().split())

    d_list = [d]
    for _ in range(g):
        for i in range(len(d_list) - 1, -1, -1):
            d_list.append(d_list[i] + 1)

    graph[x][y] = 1
    for i in d_list:
        dx, dy = direct[i%4]
        x, y = x + dx, y + dy
        if x < 0 or x > 100 or y < 0 or y > 100:
            continue
        graph[x][y] = 1

ans = 0
for x in range(100):
    for y in range(100):
        if graph[x][y] and graph[x+1][y] and graph[x][y+1] and graph[x+1][y+1]:
            ans += 1

print(ans)

