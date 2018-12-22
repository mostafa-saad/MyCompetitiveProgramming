r, s = map(int, raw_input().split())
maks = [-r for j in range(s)]
mini = [r for j in range(s)]
pomak = r
rj = []
meteor = []
for i in range(r):
    rj.append(['.' for j in range(s)])
    a = raw_input()
    for j in range(s):
        if a[j] == 'X':
            meteor.append((i, j))
            maks[j] = i
        elif a[j] == '#':
            rj[i][j] = '#'
            if mini[j] == r:
                mini[j] = i
                pomak = min(pomak, mini[j] - maks[j] - 1)
for m in meteor:
    rj[m[0] + pomak][m[1]] = 'X'
for i in range(r):
    print ''.join(rj[i])
