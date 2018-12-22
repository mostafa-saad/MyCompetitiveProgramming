lijevi = int(input())
desni = int(input())
X = int(input())

for i in range(lijevi, desni + 1):
    zbroj = 0
    kopija = i
    while i > 0:
        zbroj += i % 10
        i //= 10
    if zbroj == X:
        print(kopija)
        break

for i in range(desni, lijevi - 1, -1):
    zbroj = 0
    kopija = i
    while i > 0:
        zbroj += i % 10
        i //= 10
    if zbroj == X:
        print(kopija)
        break
