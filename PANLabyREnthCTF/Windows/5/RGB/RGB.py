#!/usr/bin/env python
# Anthony Sasadeusz
# PAN LabyREnth CTF Windows 5 - RGB

from z3 import *

value	= Int('value')
#value2	= Int('value2')
value3 	= Int('value3')
num	= Int('num')
num2	= Int('num2')

solver = Solver()

solver.add(value > 60)
solver.add(value <= 255)

#solver.add(value2 >= 0)
#solver.add(value2 < 255)

solver.add(value3 >= 0)
solver.add(value3 < 255)

solver.add(num == 168 * value3)
solver.add(num2 == 3 * value)

solver.add(value + num - 168 + value * value * 168 - value3 == 168 * (value3 * 34 + (num2 - value)) + 3744)

print("Trying to solve!!!")
print(solver.check())
print(solver.model())

