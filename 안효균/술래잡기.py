import copy

n, m, h, k = map(int, input().split())
runners = []
for _ in range(m):
    temp = list(map(int, input().split()))
    if temp[2] == 1:
        temp[2] = 'r'
    elif temp[2] == 2:
        temp[2] = 'd'
    runners.append(temp)
trees = []
for _ in range(h):
    trees.append(list(map(int, input().split())))


def make_chaser_projectory():
    pos = [n//2+1, n//2+1]
    d='u'
    projectories=[copy.deepcopy(pos)]
    directions = [d]
    cur_length=0
    length=1
    check_two=0
    
    
    while True:
    # make first loop
        cur_length += 1
        if d == 'u':
            pos[0] -= 1
        elif d == 'r':
            pos[1] += 1
        elif d == 'd':
            pos[0] += 1
        elif d =='l':
            pos[1] -= 1

        if length == cur_length:
            if d=='u':
                d='r'
            elif d=='r':
                d='d'
            elif d=='d':
                d='l'
            elif d=='l':
                d='u'
            cur_length=0
            check_two += 1
            if check_two == 2:
                length += 1
                check_two = 0
        if pos == [1,1]:
            d='d'
            
        projectories.append(copy.deepcopy(pos))
        directions.append(d)
        
        if pos==[1,1]:
            break
            
    
    
    for i in range(len(projectories)-2, 0,-1):
        next_pos = copy.deepcopy(projectories[i])
        dy = projectories[i-1][0] - projectories[i][0]
        dx = projectories[i-1][1] - projectories[i][1]
        if dy == 1:
            d = 'd'
        elif dy == -1:
            d = 'u'
        elif dx == 1:
            d = 'r'
        elif dx == -1:
            d = 'l'
        projectories.append(next_pos)
        directions.append(d)
        
    while len(projectories) < k:
        projectories.extend(projectories)
        directions.extend(directions)
                
    return projectories, directions


def move_runner(runner, chaser):
    d = runner[2]
    pos = runner[:2]
    
    # 술래와의 거리가 3 초과라면 움직이지 않음
    if abs(pos[0]-chaser[0]) + abs(pos[1]-chaser[1]) > 3:
        return runner
    
    if d == 'd':
        if pos[0]+1 <= n:
            next_pos = [pos[0]+1, pos[1]]
        else:
            next_pos = [pos[0]-1, pos[1]]
            d = 'u'
    elif d == 'u':
        if pos[0]-1 >= 1:
            next_pos = [pos[0]-1, pos[1]]
        else:
            next_pos = [pos[0]+1, pos[1]]
            d = 'd'
    elif d =='r':
        if pos[1] + 1 <= n:
            next_pos = [pos[0], pos[1]+1]
        else:
            next_pos = [pos[0], pos[1]-1]
            d = 'l'
    elif d == 'l':
        if pos[1] -1 >= 1:
            next_pos = [pos[0], pos[1]-1]
        else:
            next_pos = [pos[0], pos[1]+1]
            d = 'r'
    if next_pos == chaser:
        next_pos = pos
    next_pos.append(d)
    return next_pos


def move_1step(runners):
    new_runners = []
    for runner in runners:
        new_runners.append(move_runner(copy.deepcopy(runner), chaser))
    return new_runners

def get_points(time):
    cands = []
    point = 0
    
    if chaser_direction == 'r':
        for i in range(3):
            cands.append([chaser[0], chaser[1]+i])
    elif chaser_direction == 'l':
        for i in range(3):
            cands.append([chaser[0], chaser[1]-i])
    elif chaser_direction == 'u':
        for i in range(3):
            cands.append([chaser[0]-i, chaser[1]])
    elif chaser_direction == 'd':
        for i in range(3):
            cands.append([chaser[0]+i, chaser[1]])
            
    new_runners = []
    for runner in runners:
        if runner[:2] in cands and runner[:2] not in trees:
            point +=1
        else:
            new_runners.append(runner)
    point *= time
    return point, new_runners

chaser_projectories, chaser_directions = make_chaser_projectory()
chaser = chaser_projectories[0]
chaser_direction = chaser_directions[0]
points = 0
for t in range(1, k+1):
    runners = move_1step(runners)
    chaser = chaser_projectories[t]
    chaser_direction = chaser_directions[t]
    point, runners = get_points(t)
    points += point
print(points)
