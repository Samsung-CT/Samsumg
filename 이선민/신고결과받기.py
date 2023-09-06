def solution(id_list, report, k):
    report = list(set(report))
    # 신고당한사람: [신고한 사람, ...]
    reportDic = {}
    for tmp in report:
        user, target = tmp.split(" ")
        arr = reportDic.get(target, [])
        arr.append(user)
        reportDic[target] = arr
    # id: 메일 수
    countDic = {}
    for id in id_list:
        if id not in reportDic: continue
        if len(reportDic[id]) >= k:
            for user in reportDic[id]:
                prev = countDic.get(user, 0)
                countDic[user] = prev+1
    ans = []
    for id in id_list:
        ans.append(countDic.get(id, 0))
    return ans