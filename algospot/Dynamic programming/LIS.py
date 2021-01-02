cache = []
answer = []
lis = []
size = 0


def calLis(x, maxNum):
    global size

    if x == size-1:
        if lis[x] > maxNum:
            return 1
        else:
            return 0
    elif lis[x] > maxNum:
        if cache[x] == -1:
            cache[x] = 1 + calLis(x+1, lis[x])
        return max(cache[x], calLis(x+1, maxNum))
    else:
        return calLis(x+1, maxNum)


case = int(input())
for _ in range(case):
    size = int(input())
    cache = [-1 for _ in range(size)]
    lis = [int(x) for x in input().strip().split()]
    answer.append(calLis(0, 0))

for i in range(case):
    print(answer[i])


