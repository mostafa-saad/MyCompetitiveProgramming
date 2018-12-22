n = int(input())
niz = list(map(int, input().split()))
niz.sort(reverse=True)
ukupno = sum(niz)
a = 1
b = 1
tmp = 0
for i in range(n):
    tmp += niz[i]
    if tmp/ukupno - (i + 1)/n > b - a:
        a = (i + 1) / n
        b = tmp / ukupno
print(a * 100)
print(b * 100)
#print(a * 100, b * 100)
