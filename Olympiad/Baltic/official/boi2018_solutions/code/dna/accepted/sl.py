#!/usr/bin/env python3
n,k,r = map(int, input().split())
v = list(map(int, input().split()))
counts = [0] * k
for x in v:
    counts[x] += 1

failed = 0
have = [0] * k
wanted = [0] * k
for i in range(r):
    sym, co = map(int, input().split())
    if counts[sym] < co:
        print("impossible")
        exit(0)
    wanted[sym] = co
    failed += 1

i = j = 0
res = 1000000000
while True:
    if failed > 0:
        if j == n:
            break
        have[v[j]] += 1
        if have[v[j]] == wanted[v[j]]:
            failed -= 1
        j += 1
    else:
        dif = j - i
        if dif < res:
            res = dif
        if have[v[i]] == wanted[v[i]]:
            failed += 1
        have[v[i]] -= 1
        i += 1
print(res)
