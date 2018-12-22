N, C = map(int, raw_input().strip().split())
a = map(int, raw_input().split())

ans = 0
for i in range(N):
  left = C
  curr = 0
  for j in range(i, N):
    if a[j] <= left: 
      left -= a[j]
      curr += 1
  ans = max(ans, curr)
print ans
