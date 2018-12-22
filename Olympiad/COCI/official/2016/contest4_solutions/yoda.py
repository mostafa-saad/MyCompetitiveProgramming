a = input()
b = input()
a = str(a)
b = str(b)

while len(a) < len(b): a = "0" + a
while len(b) < len(a): b = "0" + b

na = []
nb = []

for i in range(len(a)):
  na.append(a[i])
  nb.append(b[i])
  if a[i] < b[i]: na.pop()
  if b[i] < a[i]: nb.pop()


if len(na) == 0: print "YODA" 
else: print int("".join(na))

if len(nb) == 0: print "YODA" 
else: print int("".join(nb))
