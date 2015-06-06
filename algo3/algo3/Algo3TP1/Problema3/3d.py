#!/usr/bin/env python

import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import random
from math import *

f = open('sarasa')

data = {}

n = 2
k = i = 0
for line in f:
	# Esta en segundos con 6 digitos de precision.
	value = float(line.replace("\n", ""))
	value = int(value * (1000 * 1000)) # Y ahora esta en microsecs
	if not n in data: data[n] = {}
	if not k in data[n]: data[n][k] = []
	# print n, k, i
	# print l[n]
	# print l[n][k]
	data[n][k].append(int(value))
	i+=1
	if i >= 100:
		k+=1
		i=0
	if k > n*n:
		n+=1
		k=0

# print l

def fun(n, k):

	try:
		l = data[n][k]
		# print sum(l)
		ret = (sum(l) / float(len(l)))
		print ret
		ret = (ret * (k**2)) / (2**(n))
	except: 
		ret = 0

	return ret

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = np.arange(2, 9)
y = np.arange(0, 65)
X, Y = np.meshgrid(x, y)
# print X, Y
zs = np.array([fun(x,y) for x,y in zip(np.ravel(X), np.ravel(Y))])
# print zs
Z = zs.reshape(X.shape)

ax.plot_surface(X, Y, Z)

ax.set_xlabel('N')
ax.set_ylabel('K')
ax.set_zlabel('Tiempo')

plt.show()