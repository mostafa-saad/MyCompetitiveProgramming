
rijeci = {} # rjecnik u kojem za svako slovo drzimo listu sortiranih rijeci
brojac = {} # rjecnik u kojem za svako slovo drzimo pokazivac na sljedecu rijec koju cemo ispisati
slova = 'qwertyuiopasdfghjklzxcvbnm'

for c in slova:
    rijeci[c] = []

n, m = map (int, input().split())
for i in range(n):
    rijec = input()
    rijeci[rijec[0]].append(rijec)

for c in slova:
    rijeci[c].sort()
    brojac[c] = 0

for i in range(m):
    upit = input()[0] # unosimo slovo za upit
    print(rijeci[upit][brojac[upit]])
    brojac[upit] += 1
    if brojac[upit] == len(rijeci[upit]):
        brojac[upit] = 0
