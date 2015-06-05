#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pylab import *
import math
import sys


n = []
t = [[],[],[],[],[],[]]
ts= []

read_files=['Tiempos_'+str(i*40) for i in range(1,6)]

nl=0

for i in range(5):
	nl=0
	read_file = open(read_files[i])
	for line in read_file:
		ts.append(int(line))
		if (nl%100==99):
			t[i].append(mean(ts))
			ts=[]
		nl+=1
	read_file.close()

div=int(sys.argv[1])
for j in range(5):
	for i in range(len(t[j])):
		t[j][i]/=((i+1)**div)

xmax=200
n=range(2,201,2)
colores=['#FF0000','#00FF00','#0000FF','#FFFF00','#00FFFF']
for i in range(5):
	plt.scatter(n, t[i], label="n="+str(i*40+40)+";m=20",color=colores[i]) 

plt.legend(loc=2)

barra= ''
if (div>0): barra='/s'
if (div>1): barra+= '^'+str(div)

plt.ylabel('Tiempo (Ciclos)'+barra)
plt.xlim(0,xmax)
plt.ylim(0,max(max(t[i][(xmax/10):xmax]) for i in range(5)))
plt.xlabel('Cantidad de soldados')
plt.title(u'Tiempo de Cómputo')
plt.grid(True)
plt.savefig(sys.argv[2]+'.png')
