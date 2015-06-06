from pylab import *
import math
import sys

n = []
t = [[],[],[],[],[]]
ts= []

read_files=['Tiempom_'+str(i) for i in range(20000,100001,20000)]

nl=0

for i in range(5):
	nl=0
	read_file = open(read_files[i])
	for line in read_file:
		ts.append(int(line))
		if (nl%10==9):
			t[i].append(mean(ts))
			ts=[]
		nl+=1

xmax=101000
n=range(1000,xmax,1000)
colores=['#FF0000','#00FF00','#0000FF','#FFFF00','#00FFFF','#FF00FF']
for i in range(5):
	plt.scatter(n, t[i], label="n="+str((i+1)*20000),color=colores[i])

plt.legend(loc=2)

plt.ylabel('Tiempo (Ciclos)')
plt.xlim(0,xmax)
plt.ylim(0,max(t[4]))#[(xmax/10000/1000):(xmax/1000/1000)]))
plt.xlabel('Minutos emitidos')
plt.title('Tiempo de Computo')
plt.grid(True)
plt.savefig(sys.argv[1]+'.png')
