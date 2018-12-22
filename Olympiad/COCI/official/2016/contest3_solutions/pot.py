N = int(input())

ukupno = 0

for i in range(N):
    P = int(input())

    pot = P % 10
    baza = P // 10

    potencija = 1
    for i in range(pot):
        potencija *= baza

    ukupno += potencija

print(ukupno)
