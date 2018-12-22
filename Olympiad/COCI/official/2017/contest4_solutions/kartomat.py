N = int(input())

L = []
for i in range(N):
    L += [input()]

#print(L)

odrediste = input()

s = ''
d = len(odrediste)
for i in range(N):
    #print(L[i][:d], odrediste)
    if L[i][:d] == odrediste:
        s += L[i][d]

t1 = '***ABCDE'
t2 = 'FGHIJKLM'
t3 = 'NOPQRSTU'
t4 = 'VWXYZ***'

for i in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    if i not in s:
        if i in t1:
            t1 = t1.replace(i,'*')
        if i in t2:
            t2 = t2.replace(i,'*')
        if i in t3:
            t3 = t3.replace(i,'*')
        if i in t4:
            t4 = t4.replace(i,'*')

print(t1,t2,t3,t4, sep = '\n')
