import math

n, m = map(int, input().split())
tab = [list(input()) for _ in range(n)]

charc = [0,]*26
for l in tab:
    for x in l:
        charc[ord(x)-ord('a')] += 1

chargcd = math.gcd(*charc)
templatec = [x//chargcd for x in charc]

def verifyc(ac, bc):
    ratio = -1
    for a, b in zip(ac, bc):
        if b == 0:
            if a == 0:
                continue
            else:
                return False
        if ratio == -1:
            ratio = a/b
        else:
            if ratio != a/b:
                return False
    return True

find_i, find_j = -1, -1
find_tempc = [0,]*26
find_temp = []

def _find(pos):
    global find_i, find_j, find_tempc, find_temp

    d1 = bool(pos&2)
    d2 = bool(pos&1)
    a, b = 0, 0
    while True:
        find_i += 1
        find_j += 1
        if d1 is not d2:
            if find_i+1 >= min(len(tab), len(tab[0])):
                return False
        else:
            if find_j >= min(len(tab), len(tab[0])):
                return False

        if not d1 and not d2:
            a = tab[0][find_i]
            b = tab[1][find_j]
        elif not d1 and d2:
            a = tab[0][find_i]
            b = tab[find_j+1][0]
        elif d1 and not d2:
            a = tab[find_i][0]
            b = tab[0][find_j+1]
        elif d1 and d2:
            a = tab[find_i][0]
            b = tab[find_j][1]
        
        if a != b:
            return False

        find_temp.append(a)
        
        find_tempc[ord(a)-ord('a')] += 1
        find_tempc[ord(b)-ord('a')] += 1

        if verifyc(find_tempc, templatec):
            return find_temp

find_pos = 0

def find():
    global find_pos, find_i, find_j, find_tempc, find_temp
    while find_pos < 4:
        ans = _find(find_pos)
        if ans is not False:
            return ans
        find_pos += 1
        find_i, find_j = -1, -1
        find_tempc = [0,]*26
        find_temp = []
    return False

check_lengths = set()

def reduce_lengths(n):
    global check_lengths
    for x in check_lengths.copy():
        check_lengths.add(x//n)
        check_lengths.remove(x)

def _check(pattern):
    global tab
    stack = [(0, 0, 0),]

    while stack:
        state = stack.pop()
        good = True
        for i in range(len(pattern)):
            letter = None
            if state[2] == 0:
                letter = tab[state[0]][state[1]+i]
            else:
                letter = tab[state[0]+i][state[1]]
            if letter != pattern[i]:
                good = False
                break
        if good:
            if state[2] == 0:
                stack.append((state[0], state[1]+len(pattern), 0))
            else:
                stack.append((state[0]+len(pattern), state[1], 0))
        else:
            return False
    
    return True

def explore(pos, pattern):
    stack = [(*pos, 0)]
    length = 0

    while stack:
        state = stack.pop()
        good = True
        for i in range(len(pattern)):
            letter = None
            if state[2] == 0:
                letter = tab[state[0]][state[1]+i]
            else:
                letter = tab[state[0]+i][state[1]]
            if letter != pattern[i]:
                good = False
                break
        if good:
            if state[2] == 0:
                stack.append((state[0], state[1]+len(pattern), 0))
            else:
                stack.append((state[0]+len(pattern), state[1], 0))
            length += 1
        else:
            return False
    return True

a = True
while a:
    a = find()
    if a:
        print(a, len(a))
        if _check(a):
            print("ok")