# -((-P)|Q)|(Q|(-P))

try:
    s = raw_input()
except:
    s = input()
n = ""
tmp = []
p, q = 0, 0
for item in s:
    if item == '-':
        n += ' not '
    elif item == '|':
        n += ' or '
    elif item == '*':
        n += ' and '
    else:
        n += item
v = [[0, 0], [0, 1], [1, 0], [1, 1]]
res = ""

for i in range(4):
    ls = v[i]
    for item in n:
        if item == 'P':
            res += str(ls[0])
        elif item == 'Q':
            res += str(ls[1])
        else:
            res += item
    # print(res)
    tmp.append(eval(res))
    res = ""
    # print(tmp)
# print(tmp)
result = -1
for item in tmp:
    if item == True or item ==  1:
        if result == 0:
            result = 2
            break
        result = 1
    else:
        if result == 1:
            result = 2
            break
        result = 0
        
print(result)
