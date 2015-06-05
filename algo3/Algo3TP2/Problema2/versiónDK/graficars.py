#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pylab import *
import math
import sys


n = []
t = []
ts= []

nl=0

nl=0
read_file = open('Tiempos_250')
for line in read_file:
	ts.append(int(line.split()[1]))
	if (nl%10==9):
		if not int(line.split()[0]):
			t.append(mean(ts))
		else:
			t.append(-100)
		ts=[]
	nl+=1
read_file.close()

div=int(sys.argv[1])
xmax=0
for i in range(len(t)):
	if t[i]>=0:
		t[i]/=((i+1)**div)
		if xmax<i: xmax=i
			

n=range(1,401)

#print len(n)
#print len(t[0])

plt.scatter(n, t, label="n=250;m=20",color='#FF0000') 

plt.legend(loc=2)

barra= ''
if (div>0): barra='/s'
if (div>1): barra+= '^'+str(div)

plt.ylabel('Tiempo (Ciclos)'+barra)
plt.xlim(0,xmax)
#[(xmax/10):xmax]

plt.ylim(0,max(t[20:xmax]))
plt.xlabel('Cantidad de soldados')
plt.title(u'Tiempo de Cómputo')
plt.grid(True)
plt.savefig(sys.argv[2]+'.png')
