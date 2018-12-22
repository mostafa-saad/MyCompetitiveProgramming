A = raw_input()
P, M = map(int, raw_input().strip().split(' '))

def mod (x):
  return (x[0]%M, x[1]%M)

def sum (a, b):
  return mod((a[0] + b[0], a[1] + b[1]))

def min (a, b):
  return mod((a[0] - b[0], a[1] - b[1]))

def mul (a, b):
  assert(not(a[0] > 0 and b[0] > 0))
  return mod((a[0]*b[1] + a[1]*b[0], a[1]*b[1]))

def apply (ret, c):
  if c == '+': tt = sum(ret[-2], ret[-1])
  if c == '-': tt = min(ret[-2], ret[-1])
  if c == '*': tt = mul(ret[-2], ret[-1])
  ret.pop()
  ret.pop()
  ret.append(tt)

opp = {'+': 0, '-': 0, '*': 1}

os = []
ret = []
T = []

val = 0
ok = 0

for i in range(len(A)):
  if A[i].isdigit():
    val = val*10 + int(A[i])
    ok = 1
  else:
    if ok: T.append(val)
    val = 0
    ok = 0
    T.append(A[i])

if ok: T.append(val)

for c in T:
  if c == 'x':
    ret.append((1, 0))
  elif c in opp:
    while len(os) and (os[-1] in opp) and opp[os[-1]] >= opp[c]:
      apply(ret, os[-1])
      os.pop()
    os.append(c)
  elif c == '(': os.append(c)
  elif c == ')':
    while len(os) and os[-1] != '(':
      apply(ret, os[-1])
      os.pop()
    assert(len(os) > 0)
    os.pop()
  else:
    ret.append((0, c))

for c in os[::-1]:
  apply(ret, c)

assert(len(ret) == 1)
ret = ret[0]
for i in range(0, 10**6):
  if ((ret[0]*i + ret[1])%M + M)%M == P:
    print i
    break
