N = int(input())
X = int(input())

cijena = 0

for i in range(N):
    P1, P2 = map(int, input().split())
    if abs(P1 - P2) <= X:
        cijena += max(P1, P2)
    else:
        cijena += int(input())

print(cijena)
