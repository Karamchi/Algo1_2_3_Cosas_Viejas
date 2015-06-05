from pylab import *
import math
import sys

n = []
t = []
ts= []
ka= []

read_file = open('Tiempo')

nl=0
for line in read_file:
	ts.append(int(line.split(" ")[3]))
	if (nl%10==9):
		nn=int(line.split(" ")[0])
		if (nn>6):
			n.append(nn)
			ka.append(int(line.split(" ")[1]))
			t.append(mean(ts)/nn)
		ts=[]
	nl+=1

paraprom=[]
y=[]
x=[]
for i in range(100):
	for j in range(len(ka)):
		if ka[j]==i:
			paraprom.append(t[j])
	if len(paraprom)>0:
		y.append(mean(paraprom))
		x.append(i)
		paraprom=[]
	

div=int(sys.argv[1])
#for j in range(3):
#	for i in range(len(y[j])):
#		y[j][i]/=((i+1)**div)
for i in range(len(y)):
	y[i]/=(x[i]**div)


scatter(x, y, label="Aleatorio") 

barra= ''
if (div>0): barra='/n'
ala= ''
if (div>1): ala= '^'+str(div)

legend()
ylabel('Tiempo (Ciclos)/n'+barra+ala)
ylim(0,max(y))
xlim(0,101)
xlabel('Tam. Entrada')
title('Tiempo de Computo')
grid(True)
savefig(sys.argv[2]+'.png')
