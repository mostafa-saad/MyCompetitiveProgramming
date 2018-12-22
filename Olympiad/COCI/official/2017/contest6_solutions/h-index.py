n = int(input())
a = list(map(int, input().split()))
a.sort(reverse=True)
h = 0
while h < n and a[h] >= h + 1:
    h += 1
print(h)
