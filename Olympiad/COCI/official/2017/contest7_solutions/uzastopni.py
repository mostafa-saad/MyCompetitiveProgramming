from math import sqrt

def solve(n):
    bound = int(sqrt(2 * n)) + 1
    for k in range(2, bound):
        y = n - k * (k + 1) // 2
        if y % k == 0:
            print(y // k + 1, y // k + k)

solve(int(input()))
