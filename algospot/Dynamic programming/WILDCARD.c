cache = []
answer = []
match = ""
dic = ""
lenMatch = 0
lenDic = 0


def wildCard(x, y):
    global match, dic, lenMatch, lenDic

    if cache[x][y] != -1:
        return cache[x][y]
    elif x == lenMatch-1 and y == lenDic-1:
        if match[x] == '*' or match[x] == '?' or match[x] == dic[y]:
            return True
        else:
            return False
    elif x == lenMatch-1:
        if match[x] == '*':
            return True
        else:
            return False
    elif y == lenDic:
        if match[x] == '*':
            return wildCard(x+1, y)
        else:
            return False
    else:
        if match[x] == '*':
            cache[x][y] = wildCard(x, y+1) or wildCard(x+1, y)
            return cache[x][y]
        else:
            if match[x] == dic[y] or match[x] == '?':
                cache[x][y] = wildCard(x+1, y+1)
                return cache[x][y]
            else:
                return False


case = int(input())
for _ in range(case):
    match = str(input())
    matchNum = int(input())
    lenMatch = len(match)
    temp = []
    for _ in range(matchNum):
        dic = str(input())
        lenDic = len(dic)
        cache = [[-1 for _ in range(101)] for _ in range(101)]

        if wildCard(0, 0):
            temp.append(dic)
    temp.sort()
    answer.extend(temp)

for i in range(len(answer)):
    print(answer[i])


