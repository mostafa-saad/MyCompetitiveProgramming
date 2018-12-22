def prvi_manji(n, p):
    a = n[:]
    a[p] -= 1
    while p + 1 < len(a):
        a[p + 1] = 9 - a[p] % 2
        p += 1
    return int(''.join(map(str, a)))


def prvi_veci(n, p):
    b = n[:]
    b[p] += 1
    while p + 1 < len(b):
        b[p + 1] = 1 - b[p] % 2
        p += 1
    return int(''.join(map(str, b)))


n = map(int, list(raw_input()))

# Nadji prvu znamenku koja se mora promijeniti.
p = -1
for i in range(1, len(n)):
    if n[i] % 2 == n[i - 1] % 2:
        p = i
        break

assert p != -1

if n[p] == 0:
    print prvi_veci(n, p)
elif n[p] == 9:
    print prvi_manji(n, p)
else:
    a = prvi_manji(n, p)
    b = prvi_veci(n, p)
    n = int(''.join(map(str, n)))
    if n - a > b - n:
        print b
    elif n - a < b - n:
        print a
    else:
        print a, b
