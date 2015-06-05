from pylab import *
import math
import sys

n = []
y = [[],[],[]]
ts= []
t =[]
read_files=["Tiempo_0","Tiempo_1","Tiempo_2"]

for i in range(3):
	read_file = open(read_files[i])
	
	nl=0	
	for line in read_file:
		ts.append(int(line.split(" ")[3]))
		if (nl%10==9):
			ka=int(line.split(" ")[1])
			kb=int(line.split(" ")[2])
			t.append(mean(ts)/(ka+1)/(kb+1))
			ts=[]
		if (nl%100==99):
			y[i].append(mean(t))
			t=[]
		nl+=1


div=int(sys.argv[1])
for j in range(3):
	for i in range(len(y[j])):
		y[j][i]/=((i+1)**div)
#for i in range(len(t)):
#	y[i]/=((i+1)**div)

n=range(100)
scatter(n, y[0], label="Aleatorio") 
scatter(n, y[1], label="MC", color='#FF0000') 
scatter(n, y[2], label="PC", color='#00FF00') 

barra= ''
if (div>0): barra='/n'
if (div>1): barra+= '^'+str(div)

legend()

ylabel('Tiempo (Ciclos)'+barra)
xlim(0,101)
ylim(0,max(y[2]))
xlabel('Tam. Entrada')
title('Tiempo de Computo')
grid(True)
savefig(sys.argv[2]+".png")
