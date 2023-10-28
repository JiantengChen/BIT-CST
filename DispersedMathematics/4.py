from __future__ import print_function
try:
    elements = raw_input().split(',')
except:
    elements = input().split(',')
d = {}
for item in elements:
    d[item] = {'exit': True, 'max': True, 'min': True}

try:
    t = raw_input()
except:
    t = input()
i = 0
while i < len(t):
    i += 1
    d[t[i]]['max'] = False
    i += 2
    d[t[i]]['min'] = False
    i += 3
max_elements = []
min_elements = []
for key,value in d.items():
    if value['max'] == True:
        max_elements.append(key)
    if value['min'] == True:
        min_elements.append(key)

max_elements.sort()
min_elements.sort()
for i in range(len(min_elements)):
    if i < len(min_elements)-1:
        print(min_elements[i],end=',')
    else:
        print(min_elements[i])
for i in range(len(max_elements)):
    if i < len(max_elements)-1:
        print(max_elements[i],end=',')
    else:
        print(max_elements[i])