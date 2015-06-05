#!/usr/bin/env python


import sys
from random import randint

def randomPos(k): return (randint(1, k), randint(1, k)) 

for n in range(2, 10):
	for k in range(n**2+1):
		for i in range(100):
			f = open('casos/' + str(n) + '-' + str(k) + '-' + str(i), 'w')
			f.write(str(n) + ' ' + str(k) + "\n")
			l = []
			if k == 0:
				f.close()
				# print l
				continue

			for j in range(k):
				p = randomPos(n)
				while p in l: p = randomPos(n)
				l.append(p)
			for elem in l:
				f.write(str(elem[0]) + ' ' + str(elem[1]) + "\n")

			f.close()
			# print l
