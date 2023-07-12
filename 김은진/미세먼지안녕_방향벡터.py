import sys
si = sys.stdin.readline


def spread():
  tmp = [[0] * c for _ in range(r)]
  tmp[clr][0] = -1
  tmp[clr + 1][0] = -1

  for x in range(r):
    for y in range(c):
      if graph[x][y] > 0:
        tmp[x][y] += graph[x][y]
        for dx, dy in (-1, 0), (1, 0), (0, -1), (0, 1):
          nx, ny = x + dx, y + dy
          if (0 <= nx < r) and (0 <= ny < c) and graph[nx][ny] > -1:
            tmp[nx][ny] += int(graph[x][y] / 5)
            tmp[x][y] -= int(graph[x][y] / 5)

  return tmp


def clean_air(x, y, cycle):
  tmp = 0

  for dx, dy in cycle:
    while True:
      nx, ny = x + dx, y + dy

      if (nx == clr or nx == clr + 1) and ny == 0:
        break
      elif (0 <= nx < r) and (0 <= ny < c):
        tmp, graph[nx][ny] = graph[nx][ny], tmp
        x, y = nx, ny
      else:
        break


r, c, t = map(int, si().split())
graph = [list(map(int, si().split())) for _ in range(r)]

clr = -1  # 공기청정기 x index (공기청정기는 항상 1번 열에 설치)
for i in range(r):
  if graph[i][0] == -1:
    clr = i
    break


up = [(0, 1), (-1, 0), (0, -1), (1, 0)]  # 위쪽 공기청정기의 바람은 반시계방향
down = [(0, 1), (1, 0), (0, -1), (-1, 0)] # 아래쪽 공기청정기의 바람은 시계방향으

for _ in range(t):
  graph = spread()  # 미세먼지가 확산
  clean_air(clr, 0, up)  # 위쪽 공기청정기가 작동
  clean_air(clr + 1, 0, down)  # 아래쪽 공기청정기가 작동

print(sum([sum(graph[i]) for i in range(r)]) + 2)
