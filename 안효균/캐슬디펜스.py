N,M,D = map(int, input().split())
board = []
for _ in range(N):
    board.append(list(map(int, input().split())))
    
enems = []
for row in range(N):
    for col in range(M):
        if board[row][col] == 1:
            enems.append([row,col])

def combination(arr, m, chosen):
    if m == 0:
        combs.append(chosen[:])
        return
    
    if len(chosen) == 0:
        start = 0
    else:
        start = arr.index(chosen[-1]) + 1
        
    for index in range(start, len(arr)):
        chosen.append(arr[index])
        combination(arr, m-1, chosen)
        chosen.remove(arr[index])
    
def attack():
    enems_to_del = []
    for arch in archers:
        # 공격할 적 탐색
        min_distance = 1000
        enem_to_del = None
        for enem in enems:
            distance = abs(enem[0]-arch[0]) + abs(enem[1]-arch[1])
            if distance > D:
                continue
            if distance < min_distance:
                min_distance = distance
                enem_to_del = (enem[0],enem[1])
            if distance == min_distance:
                if enem[1] < enem_to_del[1]:
                    enem_to_del = (enem[0],enem[1])
        if enem_to_del:
            enems_to_del.append(enem_to_del)
    # 중복 제거
    enems_to_del = set(enems_to_del)
    point = len(enems_to_del)
    for enem in enems_to_del:
        enems.remove([enem[0],enem[1]])
    return point


def move():
    new_enems = []
    for enem in enems:
        enem[0] += 1
        if enem[0] == N:
            continue
        new_enems.append(enem[:])
    return new_enems

combs = []
combination(list(range(M)), 3, [])
max_point = 0
enems_copy = [L[:] for L in enems]
for comb in combs:
    enems = [L[:] for L in enems_copy]
    archers = []
    for col in comb:
        archers.append([N,col])

    point = 0
    while len(enems) > 0:
        point += attack()
        enems = move()
    max_point = max(max_point, point)
print(max_point)
