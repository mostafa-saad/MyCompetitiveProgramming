N = int(input())

stol = []
for i in range(N):
    Ti, Zi = map(int, input().split())
    stol += [[i, Ti, Zi]]
#print(stol)

stol = sorted(stol, key = lambda x: x[2])

#print(stol)

for i in range(N-1):
    koliko = stol[i][1]
    j = i + 1
    while koliko > 0 and j < N:
        t = stol[j][1]
        stol[j][1] = min(stol[j][2], stol[j][1] + koliko)
        koliko = koliko - (stol[j][1] - t)
        stol[i][1] = koliko
        j += 1

    #print(stol)

stol = sorted(stol, key = lambda x: x[0])
#print(stol)

ukupno = 0
for i in range(N):
    if stol[i][1] == 0:
        ukupno += 1
print(ukupno)

for i in range(N):
    print(stol[i][1], end = ' ')
