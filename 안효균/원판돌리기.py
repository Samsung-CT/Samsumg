import copy
import sys

sys.setrecursionlimit(10**7)

N, M, T = map(int, input().split())
circle = [[-1 for _ in range(M)]]
rotations = []
for i in range(N):
    temp = list(map(int, input().split()))
    circle.append(temp)
for i in range(T):
    temp = list(map(int, input().split()))
    rotations.append(temp)

def rotation_(cir, d, k):
    # d=0 -> 시계, d=1 -> 반시계
    # k칸만큼 이동 후 M으로 나눈 나머지. 
    cir_temp = [-1 for _ in range(M)]
    for idx in range(M):
        if d == 0:
            new_idx = (idx + k) % M
        elif d == 1:
            new_idx = (idx - k) % M
        cir_temp[new_idx] = cir[idx]
    return cir_temp
    
    
def rotation(x, d, k):
    for num in range(x, N+1, x):
        new_cir = rotation_(copy.deepcopy(circle[num]), d, k)
        circle[num] = new_cir
    return


def find_adj(i, j):
    cands = [[i+1,j], [i-1,j], [i,j+1], [i,j-1]]
    # ** 0번째와 M번째도 인접
    if j == M-1:
        cands.append([i,0])
    elif j == 0:
        cands.append([i,M-1])
        
    temp = []
    for cand in cands:
        if N >= cand[0] > 0 and M > cand[1] >= 0:
            temp.append(cand)
    return temp


def dfs(i, j, val, visited=[]):
    visited.append([i,j])
    
    adjs = find_adj(i,j)
    for adj in adjs:
        value = circle[adj[0]][adj[1]]
        if adj not in visited and value != 'x' and value == val:
            visited = dfs(adj[0], adj[1], val, visited)
            
    if len(visited) > 1:
        return visited
    else:
        return []
            

def action():
    visited = []
    for i in range(1, N+1):
        for j in range(M):
            if [i,j] in visited:
                continue
            visited_ = dfs(i, j, circle[i][j], [])
            # print("visited_ : ", visited_)
            visited.extend(visited_)
    # print("visited : ", visited)
    
    if len(visited) > 0:
        for pos in visited:
            circle[pos[0]][pos[1]] = 'x'
    else:
        Sum = 0
        count = 0
        for i in range(1, N+1):
            for j in range(M):
                value = circle[i][j]
                if value != 'x':
                    Sum += value
                    count += 1
        if count == 0:
            return "zero"
        Mean = Sum/count
        for i in range(1, N+1):
            for j in range(M):
                value = circle[i][j]
                if value == 'x':
                    continue
                if value > Mean:
                    circle[i][j] = value-1
                elif value < Mean:
                    circle[i][j] = value+1
                    
result = 0
for rot in rotations:
    x,d,k = rot
    rotation(x,d,k)
    result = action()
    # print("rotated : ", circle)
    if result == "zero":
        print(0)
        break

if result != "zero":
    Sum = 0
    for i in range(1, N+1):
        for j in range(M):
            value = circle[i][j]
            if value != 'x':
                Sum += value
    print(Sum)
