#!/bin/python

i = 0
res = 6226274
while i < 6:
    res = res + ((ord("B") ^ res) % 0x539)
    i+=1
print(res)
