def prebroji_1(i,dx):
    duljina = 0
    while i > 0 and i + dx < N and (razlika[i] - razlika[i+dx] == dx):
        duljina += 1
        i += dx
    return duljina

def prebroji_2(i,dx):
    duljina = 0
    while i > 0 and i + dx < N and (razlika[i] - razlika[i+dx] == -dx):
        duljina += 1
        i += dx
    return duljina

N = int(input())

city = protivnik = 0
razlika = [0] * N
nule = []

for i in range(N):
    gol = int(input())

    if gol == 1:
        city += 1
    else:
        protivnik += 1

    razlika[i] = city - protivnik

    if razlika[i] == 0:
        nule += [i]

print(city, protivnik)
print(razlika.count(0) + 1)

preokret = 0
for i in nule:
    lijevo = prebroji_1(i,-1)
    desno = prebroji_1(i,1)
    if lijevo != 0 and desno != 0 and lijevo + desno > preokret:
        preokret = lijevo + desno
    lijevo = prebroji_2(i,-1)
    desno = prebroji_2(i,1)
    if lijevo != 0 and desno != 0 and lijevo + desno > preokret:
        preokret = lijevo + desno

print(preokret)
