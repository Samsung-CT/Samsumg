import heapq
from collections import deque

# 제출용
N, M, K = list(map(int, input().split()))
board = []
for _ in range(N):
    board.append(list(map(int, input().split())))
recent_attack = [[0 for _ in range(M)] for __ in range(N)]

def make_heapq():
    queue1 = []
    queue2 = []
    for row in range(N):
        for col in range(M):
            if board[row][col] > 0:
                # 공격력, 최근 공격, 행+열, 열
                queue1.append((board[row][col], -recent_attack[row][col], -row-col, -col, row))
                queue2.append((-board[row][col], recent_attack[row][col], row+col, col, -row))
    return queue1, queue2



def find_attacker():
    heapq.heapify(queue1)
    attacker = heapq.heappop(queue1)
    return  attacker

def find_attacked():
    heapq.heapify(queue2)
    attacked = heapq.heappop(queue2)
    return  attacked


def laser(start, target):
    queue = deque([start])
    visited = [[False for _ in range(M)] for __ in range(N)]
    visited[start[0]][start[1]] = True
    track_board = [b[:] for b in board]

    Found = False
    while queue:
        visit = queue.popleft()
        r, c = visit
        for cand in [[r,c+1], [r+1,c], [r,c-1], [r-1,c]]:
            cand[0] = cand[0] % N
            cand[1] = cand[1] % M
            if board[cand[0]][cand[1]] <=0:
                continue
            if visited[cand[0]][cand[1]] == True:
                continue
            visited[cand[0]][cand[1]] = True
            queue.append([cand[0], cand[1]])
            track_board[cand[0]][cand[1]] = [r,c]
            if cand == target:
                Found = True
                break

    if Found == True:
        # 역방향으로 경로 추적
        reverse_track = [target]
        while True:
            q = reverse_track[-1]
            next = track_board[q[0]][q[1]]
            if next == start:
                return reverse_track[::-1]
            reverse_track.append(next)

    else:
        return False


def cannon(attacker, target):
    track = []
    dxy = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1), (0,0)]
    for dx, dy in dxy:
        cand = [(target[0]+dx)%N, (target[1]+dy)%M]
        if cand == attacker:
            continue
        if board[cand[0]][cand[1]] <= 0:
            continue
        else:
            track.append(cand)

    return  track

def destroy():
    num = 0
    for row in range(N):
        for col in range(M):
            if board[row][col] > 0:
                num += 1
            else:
                board[row][col] = 0
    if num == 1:
        return True
    elif num > 1:
        return False
    elif num < 1:
        print("EEEEEEEEEEEEEEEEe")
        return True

def restore(track, attacker, target):
    to_restore = [[row, col] for row in range(N) for col in range(M)]
    for t in track:
        to_restore.remove([t[0], t[1]])

    to_restore.remove(attacker)
    to_restore.remove(target)
    # to_restore.remove((attacker[0], attacker[1]))
    for row,col in to_restore:
        if board[row][col] > 0:
            board[row][col] += 1
    '''for row in range(N):
        for col in range(M):
            if [row, col] in track:
                continue
            elif [row, col] == attacker:
                continue
            else:
                board[row][col] += 1'''
    return

def action(t):
    global board
    attacker = find_attacker()
    # 공격력 + (N+M)
    damage, recent_att, rowcol, col, row = attacker
    col *= -1
    damage += N+M
    board[row][col] = damage
    half_damage = damage//2
    attacked = find_attacked()
    _, __, ___, col_, row_ = [a for a in attacked]
    row_ *= -1
    recent_attack[row][col] = t

    track = laser(start=[row,col], target=[row_, col_])
    if track == False:
        track = cannon([row,col], [row_, col_])
    if [row, col] in track:
        track.remove([row, col])
    if [row_, col_] in track:
        track.remove([row_, col_])
    board[row_][col_] -= damage



    for trk in track:
        board[trk[0]][trk[1]] -= half_damage

    isEnd = destroy() #
    if isEnd == True:
        return isEnd
    restore(track, [row, col], [row_, col_])
    return isEnd

for t in range(1, K+1):
    queue1, queue2 = make_heapq()
    isEnd = action(t)
    if isEnd == True:
        break

print(max(map(max, board)))
