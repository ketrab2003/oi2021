
def finditer(q, s):
    for i in range(len(s)):
        if s[i:].startswith(q):
            yield i

def load_data(file):
    with open(file, 'r') as f:
        n, _ = map(int, f.readline().split())
        return [list(f.readline().strip()) for _ in range(n)]

def load_ans(file):
    with open(file, 'r') as f:
        return [*map(list, f.readlines()[1].split())]

# tab = load_data('../ocen-linux/in/dru1.in')
tab = load_data('dru0.in')
#ans = load_ans('../ocen-linux/out/dru1.out')

ans = 'abaa'

def checkline(tab, ans):
    locked = []
    found = False

    if len(tab[0]) % len(ans) != 0:
        return False
    target_locked = len(tab[0]) // len(ans)

    print(f'target {target_locked}')

    for line in tab:
        print(f'next line: {line} {locked}')
        for res in finditer(ans, line):
            print(res)
            if res % len(ans) != 0:
                continue
            if res not in locked:
                locked.append(res)

            if len(locked) == target_locked:
                found = True
                break
        if found:
            break
    
    if found:
        # remove all locked
        for i, l in enumerate(locked):
            tab[i] = tab[i][:l] + tab[i][l+len(ans):]
    
    print(f'found?: {found}')

    return found

def check(tab, ans):
    tabh = [*map(''.join, tab)]
    tabv = [*map(''.join, zip(*tab))]

    print('\n'.join(tabh))

    while tabh:
        # check horizontal
        print('\niteration')
        if checkline(tabh, ans):
            print('found h')
            tabv = [*map(''.join, zip(*tabh))]
        elif checkline(tabv, ans):
            print('found v')
            tabh = [*map(''.join, zip(*tabv))]
        else:
            return False

        print('\n'.join(tabh))
        input()

    return True

    # print(tabw, tabh)

check(tab, ans)