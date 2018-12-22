redci = []
redci.append('1234567890-=')
redci.append('QWERTYUIOP[]')
redci.append('ASDFGHJKL;\'')
redci.append('ZXCVBNM,./')

prsti = '012334456777'

s = [0 for i in range(8)]

niz = raw_input()
for c in niz:
    for i in range(4):
        for j in range(len(redci[i])):
            if redci[i][j] == c:
                s[int(prsti[j])] += 1

assert len(niz) == sum(s)

for i in range(8):
    print s[i]
