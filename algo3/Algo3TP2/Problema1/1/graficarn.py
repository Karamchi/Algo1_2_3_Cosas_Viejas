from pylab import *
import math
import sys

n = []
t = []
ts= []

read_file = open('Tiempo')

nl=0
for line in read_file:
	ts.append(int(line.split(" ")[1]))
	if (nl%100==99):
		n.append(int(line.split(" ")[0]))
		t.append(mean(ts))
		ts=[]
	nl+=1

	#values.append((suma/lim)/(n*math.log(n, 2)))

div=int(sys.argv[1])
#for j in range(3):
#	for i in range(len(t[j])):
#		t[j][i]/=((i+1)**div)
for i in range(len(t)):
	t[i]/=((i+1)**div)

scatter(n, t, label="Aleatorio") 

barra= ''
if (div>0): barra='/n'
ala= ''
if (div>1): ala= '^'+str(div)

legend()

ylabel('Tiempo (Ciclos)'+ala+barra)
xlim(0,101)
ylim(0,max(t))
xlabel('Tam. Entrada')
title('Tiempo de Computo')
grid(True)
savefig(sys.argv[2]+".png")
