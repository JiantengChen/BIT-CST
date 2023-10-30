from __future__ import print_function
matrix = []

try:
    matrix.append(raw_input().split())
except:
    matrix.append(input().split())
x = len(matrix[0])
for i in range(x-1):
    try:
        matrix.append(raw_input().split())
    except:
        matrix.append(input().split())

n = len(matrix)

flag_1 = 1
for i in range(n):
    if matrix[i][i] == '0':
        flag_1 = 0
        break
print('Y' if flag_1 else 'N')


matrix_T = [[matrix[j][i] for j in range(n)] for i in range(n)]
# flag_2 = 1
# for i in range(n):
#     for j in range(n):
#         if matrix[i][j]!=matrix[j][i]:
#             flag_2 = 0
#             break
if matrix == matrix_T:
    flag_2 = 1
else:
    flag_2 = 0
print('Y' if flag_2 else 'N')


flag_3 = 1
# matrix_multiplication = [[0 for i in range(n)]for j in range(n)]
res = [[sum(map(lambda a: eval(a[0])*eval(a[1]), zip(l, s)))
        for l in zip(*matrix)]for s in matrix]

for i in range(n):
    for j in range(n):
        if res[i][j] == 1:
            if matrix[i][j] != '1':
                flag_3 = 0
                break

# for i in range(n):
#     for j in range(n):
#         for k in range(n):
#             if (matrix[i][j] and matrix[j][k] and not matrix[i][k]):
#                 flag_3 = 0
#                 break
print('Y' if flag_3 else 'N')

print('Y' if flag_3 and flag_1 and flag_2 else 'N')
