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
		if (nl%10==9):
			t[i].append(mean(ts))
			ts=[]
		nl+=1

div=int(sys.argv[1])
logdiv=int(sys.argv[2])
for j in range(4):
	for i in range(len(t[j])):
		t[j][i]/=(((i+1)*1000)**div)
		t[j][i]/=(math.log(((i+1)*1000),2)**logdiv)

xmax=101000
n=range(1000,xmax,1000)

plt.scatter(n, t[0], label="Aleatorio") 
plt.scatter(n, t[1], label="Mejor Caso", color='#FF0000') 
plt.scatter(n, t[2], label="Adyacentes", color='#00FF00') 
plt.scatter(n, t[3], label="Piramide", color='#00FFFF') 

plt.legend(loc=2)

barra= ''
if (div>0 or logdiv>0): barra='/'
if (div>0 and logdiv>0): barra+='('
if (div>0): barra+='n'
if (div>1): barra+= '^'+str(div)
if (div>0 and logdiv>0): barra+=' '
if (logdiv>0): barra+= 'log'
if (logdiv>1): barra+= '^'+str(logdiv)
if (logdiv>0): barra+= 'n'
if (div>0 and logdiv>0): barra+=')'

plt.ylabel('Tiempo (Ciclos)'+barra)
plt.xlim(0,xmax)
plt.ylim(0,max(t[3][(xmax/10000):(xmax/1000)]))
plt.xlabel('Tam. Entrada')
plt.title('Tiempo de Computo')
plt.grid(True)
plt.savefig(sys.argv[3]+'.png')
