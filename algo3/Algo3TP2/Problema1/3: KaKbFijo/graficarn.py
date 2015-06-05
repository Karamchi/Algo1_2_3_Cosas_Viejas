from pylab import *
import math
import sys

n = []
t = [[],[],[],[],[],[]]
ts= []

read_files=['Tiempon_'+str(i*20) for i in range(6)]

nl=0

for i in range(6):
	nl=0
	read_file = open(read_files[i])
	for line in read_file:
		ts.append(int(line.split(" ")[3]))
		if (nl%100==99):
			t[i].append(mean(ts))
			ts=[]
		nl+=1
	read_file.close()

xmax=1000
n=range(1,xmax,10)

div=int(sys.argv[1])
for j in range(6):
	for i in range(len(t[j])):
		t[j][i]/=((n[i])**div)

colores=['#FF0000','#00FF00','#0000FF','#FFFF00','#00FFFF','#FF00FF']
for i in range(6):
	plt.scatter(n, t[i], label="ka="+str(i*20)+";kb=20",color=colores[i])

plt.legend(loc=2)
barra= ''
if (div>0): barra='/n'
if (div>1): barra+= '^'+str(div)

plt.ylabel('Tiempo (Ciclos)'+barra)
plt.xlim(0,xmax)
plt.ylim(0,max(max(t[i][(xmax/100):(xmax/10)]) for i in range(6)))
plt.xlabel('Tam. Entrada')
plt.title('Tiempo de Computo')
plt.grid(True)
plt.savefig(sys.argv[2]+'.png')
