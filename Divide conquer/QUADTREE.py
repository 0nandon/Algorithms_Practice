answer = []

check = 0

def reverseQuad(quad):
    global check

    if quad[check] == 'w':
        check += 1
        return "w"
    elif quad[check] == 'b':
        check += 1
        return "b"
    else:
        check += 1
        first = reverseQuad(quad)
        second = reverseQuad(quad)
        third = reverseQuad(quad)
        fourth = reverseQuad(quad)
        return "x" + third+fourth+first+second


case = int(input())
for i in range(case):
    quadTree = str(input())
    answer.append(reverseQuad(quadTree))
    check = 0

for i in range(case):
    print(answer[i])

