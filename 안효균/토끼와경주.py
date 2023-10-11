import heapq

rabbits_id = []
rabbits_dist = {}
rabbits_score = {}
pqueue = []
global_score = 0
# 제출용
Q = int(input())
prompts = []
ready = input().split()
N, M, P = list(map(int, ready[1:4]))

for idx, item in enumerate(ready[4:]):
    if idx % 2 == 0:
        id_ = int(item)
        rabbits_id.append(id_)
        rabbits_score[id_] = 0
        heapq.heappush(pqueue, (0, 0, 0, 0, id_))
    if idx % 2 == 1:
        rabbits_dist[id_] = int(item)
prompts = []
for _ in range(Q - 1):
    prompts.append(input().split())

# ide 용
# with open("input.txt", "r") as f:
#     inputs = f.readlines()
# inputs = [inp.strip().split() for inp in inputs]
# Q = int(inputs[0][0])
# ready = inputs[1]
# N, M, P = list(map(int, ready[1:4]))
# for idx, item in enumerate(ready[4:]):
#     if idx % 2 == 0:
#         id_ = int(item)
#         rabbits_id.append(id_)
#         rabbits_pos[id_] = [0, 0]
#         rabbits_score[id_] = 0
#         heapq.heappush(pqueue, (0, 0, 0, 0, id_))
#     if idx % 2 == 1:
#         rabbits_dist[id_] = int(item)
# prompts = inputs[2:]

def 이동(pos, dist, d):
    if d == "r" or d == "l":
        dist = dist % (2 * M - 2)
        L = M
        p = pos[1]
    elif d == "u" or d == "d":
        dist = dist % (2 * N - 2)
        p = pos[0]
        L = N
    while dist > 0:
        if d == "r" or d == "d":
            # 종료조건
            if dist + p <= L - 1:
                p += dist
                break
            else:
                distance = L - p
                dist -= distance
                p = L - 2
                if d == "r":
                    d = "l"
                elif d == "d":
                    d = "u"
        elif d == "l" or d == "u":
            # 종료조건
            if p - dist >= 0:
                p -= dist
                break
            else:
                distance = p + 1
                dist -= distance
                p = 1
                if d == "l":
                    d = "r"
                elif d == "u":
                    d = "d"
    if d == "r" or d == "l":
        pos[1] = p
    elif d == "u" or d == "d":
        pos[0] = p

    return pos


def 경주진행():
    # 우선순위가 높은 토끼 찾고 이동
    # 총 점프 횟수가 적은, 서있는 row+col이 작은, row가 작은, col이 작은, id가 작은
    jump, rowcol, row, col, rep_id = heapq.heappop(pqueue)


    # 다음 이동 위치 정하기
    cands = []
    for d in ["u", "d", "r", "l"]:
        cands.append(이동([row, col], rabbits_dist[rep_id], d))
    cands = sorted(cands, key=lambda x: (x[0] + x[1], x[0], x[1]), reverse=True)
    next_pos = cands[0]
    heapq.heappush(pqueue, (jump+1, sum(next_pos), next_pos[0], next_pos[1], rep_id))
    뽑힌토끼.append((-sum(next_pos), -next_pos[0], -next_pos[1], -rep_id))
    return rep_id, next_pos


def 경주후우선순위(뽑힌토끼):
    rowcol, row, col, rep_id_ = heapq.heappop(뽑힌토끼)
    return -rep_id_


for prompt in prompts:
    if prompt[0] == "200":
        K, S = map(int, prompt[1:])
        뽑힌토끼 = []
        for k in range(K):
            rep_id, next_pos = 경주진행()
            # 나머지 토끼들에 점수 주기
            global_score += sum(next_pos) + 2
            rabbits_score[rep_id] -= sum(next_pos) + 2
            # for id_ in rabbits_id:
            #     if id_ == rep_id:
            #         continue
            #     rabbits_score[id_] += sum(next_pos) + 2
            # 뽑힌토끼[rep_id] = True
        heapq.heapify(뽑힌토끼)
        id_ = 경주후우선순위(뽑힌토끼)
        rabbits_score[id_] += S

    elif prompt[0] == "300":
        id_, L = map(int, prompt[1:])
        rabbits_dist[id_] *= L

    elif prompt[0] == "400":
        print(max(rabbits_score.values()) + global_score)
