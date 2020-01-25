#!/usr/bin/python3

def main():
    n, k = map(int, input().split())
    code = []
    i = 0
    while (1 << i) < n:
        p = (1 << (1 << i)) - 1
        while p < (1 << n):
            p = p << (1 << (i + 1)) | ((1 << (1 << i)) - 1)
        p &= (1 << n) - 1
        q = ((1 << (1 << i)) - 1) << (1 << i)
        while q < (1 << n):
            q = q << (1 << (i + 1)) | ((1 << (1 << i)) - 1) << (1 << i)
        q &= (1 << n) - 1
        code.append("A=((A&" + str(p) + ")+((A&" + str(q) + ")>>(1<<" + str(i) + ")))")
        i += 1

    print(len(code))
    for line in code:
        print(line)


if __name__ == '__main__':
    main()
