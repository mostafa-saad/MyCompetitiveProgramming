n = int(raw_input())

formacije = []

for i in range(0, n):
    a, b, c = map(int, raw_input().split('-'))
    formacije.append((a,b,c))

o = 0
v = 0
n = 0
ov = 0
vn = 0
on = 0
ovn = 0

m = int(raw_input())

for j in range(0, m):
    s = ''.join(sorted(raw_input().strip()))
    if s == 'N': n = n+1
    if s == 'O': o = o+1
    if s == 'V': v = v+1
    if s == 'NO': on = on+1
    if s == 'NV': vn = vn+1
    if s == 'OV': ov = ov+1
    if s == 'NOV': ovn = ovn+1

for (O,V,N) in formacije:
    moze = 0
    for a in range(0, ov+1):
      for b in range(0, vn+1):
        for c in range(0, on+1):
          TO = max(0, O-o-a-c)
          TV = max(0, V-v-(ov-a)-b)
          TN = max(0, N-n-(vn-b)-(on-c))
          if(TO+TV+TN <= ovn): moze = 1
    if moze: 
      print "DA"
    else:
      print "NE"

