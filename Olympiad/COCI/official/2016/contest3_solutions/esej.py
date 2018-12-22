import sys
a, b = map(int, input().split())
for i in range(1, b+1):
    x = i
    while x > 0:
        sys.stdout.write(chr(x % 10 + ord('a')))
        x //= 10
    sys.stdout.write(' ')
print()
