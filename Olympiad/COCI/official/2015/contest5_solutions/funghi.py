a = []
for i in range(8):
    a.append(input())
a += a
maks = 0
for i in range(8):
    maks = max(maks, a[i] + a[i + 1] + a[i + 2] + a[i + 3])
print maks
