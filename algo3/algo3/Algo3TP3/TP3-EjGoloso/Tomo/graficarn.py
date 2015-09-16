from pylab import *
import math
import sys

n = []
t = [[],[],[],[]]
ts= []

read_files=['Tiempo0','Tiempo1','Tiempo2','Tiempo3']

nl=0

for i in range(4):
	nl=0
	read_file = open(read_files[i])
	for line in read_file:
		ts.append(int(line))
		if (nl%100==99):
			t[i].append(mean(ts))
			ts=[]
		nl+=1

div=int(sys.argv[1])
for j in range(4):
	for i in range(len(t[j])):
			t[j][i]/=(i+1)**div

xmax=149
n=range(xmax)

plt.scatter(n, t[0], label="m=0", color='#FF0000') 
plt.scatter(n, t[1], label="m=n(n-1)/2", color='#00FF00') 
plt.scatter(n, t[2], label="m aleatorio") 
plt.scatter(n, t[3], label="Cn", color='#FFFF00') 

plt.legend(loc=2)

barra= ''
if (div>0): barra='/n'
if (div>1): barra+= '^'+str(div)

plt.ylabel('Tiempo (Ciclos)'+barra)
plt.xlim(0,xmax)
plt.ylim(0,max(t[1][(xmax/10):xmax]))
plt.xlabel('Cantidad de nodos')
plt.title('Tiempo de Computo')
plt.grid(True)
plt.savefig(sys.argv[2]+'.png')
