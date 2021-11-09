import ast
import re
import sys

MOD_LIMIT = 1_000_000_007

n = int(input())
tab = [*map(int, input().split())]

visited = [0,] * (n+1)
left_count = n

# check
for i in range(n):
    if visited[tab[i]] > 0:
        print(0)
        sys.exit()
    if i+2 < n and tab[i] == tab[i+2]:
        if visited[tab[i]] == 0:
            visited[tab[i]] = -1
        else:
            print(0)
            sys.exit()
    else:
        visited[tab[i]] = 1
        left_count -= 1

if left_count == 0:
    if n%2 == 0:
        print(1)
    else:
        print(0)
    sys.exit()

# calculate

def fac(n):
    s = 1
    for i in range(n):
        s *= i+1
        s %= MOD_LIMIT
    return s

tab1 = tab[::2]
tab2 = tab[1::2]

def groupby_dup(tab):
    tab = str(tab)
    tab = tab.replace('[', '[[').replace(']', ', ], ]')
    tab = re.sub(r'(?<=[\[\] ])(\d+), \1, ', r'], [', tab)
    return ast.literal_eval(tab)

tab1 = groupby_dup(tab1)[1:]
tab2 = groupby_dup(tab2)

if n%2 == 1:
    tab1 = tab1[:-1]
else:
    tab2 = tab2[:-1]

poss = fac(left_count)

print(f'initial: {poss}')

for g in tab1:
    print(f'{poss} * {len(g)+1}')
    poss *= len(g)+1
    poss %= MOD_LIMIT

print()

for g in tab2:
    print(f'{poss} * {len(g)+1}')
    poss *= len(g)+1
    poss %= MOD_LIMIT

print(poss)