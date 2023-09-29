import copy
from collections import deque

#
n, m, c = map(int, input().split())
board = []
for _ in range(n):
    board.append(list(map(int, input().split())))
car = list(map(int, input().split()))
car = [car[0]-1, car[1]-1]
customers = []
for _ in range(m):
    customers.append(list(map(int, input().split())))
customers = [[c[0]-1, c[1]-1, c[2]-1, c[3]-1] for c in customers]



### BFS
import time
from collections import deque

dx = [1,-1,0,0]
dy = [0,0,1,-1]

def find_nextcustomer(start, left_customers):
    distance = 0
    visited = [[False for _ in range(n)] for __ in range(n)]
    queue = deque([[start, distance]])
    results = []
    
    while len(queue) > 0:
        start = queue.popleft()
        
        visit = start[0]
        distance = start[1]
        
        if visited[visit[0]][visit[1]] == True:
            continue
            
        if (visit[0], visit[1]) in left_customers:
            results.append([(visit[0], visit[1]), distance])

        visited[visit[0]][visit[1]] = True
        
        for i in range(4):
            link = [visit[0]+dx[i], visit[1]+dy[i]]
            if n<=link[0] or link[0]<0:
                continue
            if n<=link[1] or link[1]<0:
                continue
            if board[link[0]][link[1]] == 1:
                continue
            if visited[link[0]][link[1]] == False:
                queue.append([link, distance+1])
    if len(results) == 0:
        return -1, -1
    customers = sorted(results, key=lambda x: (x[1], x[0][0], x[0][1]))
    
    customer = customers[0][0]
    distance = customers[0][1]
    return customer, distance
 
    
def cal_distance(start, end):
    distance = 0
    visited = [[False for _ in range(n)] for __ in range(n)]
    queue = deque([[start, 0]])
    
    while len(queue) > 0:
        v = queue.popleft()
        visit = v[0]
        distance = v[1]
        for i in range(4):
            link = (visit[0]+dx[i], visit[1]+dy[i])
            if link == end:
                return distance+1
            if link[0] >= n or link[0] < 0:
                continue
            if link[1] >= n or link[1] < 0:
                continue
            if visited[link[0]][link[1]] == True:
                continue
            if board[link[0]][link[1]] == 1:
                continue
            visited[link[0]][link[1]] = True
            queue.append([link, distance+1])
    return -1

    
def bfs_1step(visited, queue):
    next_queue = deque([])
    for start in queue:
        visited.append(start)
        links = [[start[0]+1, start[1]], [start[0]-1, start[1]], [start[0], start[1]+1], [start[0], start[1]-1]]
        for link in links:
            if n>link[0]>=0 and n>link[1]>=0 and board[link[0]][link[1]] == 0 and link not in visited and link not in queue:
                next_queue.append(link)
    return visited, next_queue

t = time.time()

def solution(customers, car, c):
    customers = {(cus[0], cus[1]):[cus[2], cus[3]] for cus in customers}
    left_customers = list(customers.keys())
    while len(left_customers) > 0:
        next_customer, distance = find_nextcustomer(car, left_customers)
        if next_customer == -1:
            return -1
        c -= distance
        if c < 0:
            return -1
        end = customers[next_customer]
        destination_dis = cal_distance(next_customer, (end[0], end[1]))
        if destination_dis == -1:
            return -1
        c -= destination_dis
        if c < 0:
            return -1
        c += destination_dis * 2

        car = customers[next_customer]
        left_customers.remove((next_customer[0], next_customer[1]))

    return c
print(solution(customers, car, c))
