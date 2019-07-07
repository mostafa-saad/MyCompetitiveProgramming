#!/usr/bin/env python3

from decimal import *

a, b, c = map(Decimal, input().split())
print(a * b / c)
