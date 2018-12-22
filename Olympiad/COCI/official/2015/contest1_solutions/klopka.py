n = input()
mx = 101
my = 101
Mx = 0
My = 0
for i in range(n):
    x, y = raw_input().split()
    x, y = [int(x), int(y)]
    mx = min(mx, x)
    my = min(my, y)
    Mx = max(Mx, x)
    My = max(My, y)
print max(Mx - mx, My - my) ** 2
