from pylab import *
import math
import sys

n = []
t = [[],[],[]]
ts= []
read_files=["Tiempon_0","Tiempon_1","Tiempon_2"]

for i in range(3):
	read_file = open(read_files[i])
	
	nl=0	
	for line in read_file:
		ts.append(int(line.split(" ")[3]))
		if (nl%100==99):
			t[i].append(mean(ts))
			ts=[]
		nl+=1


div=int(sys.argv[1])
for j in range(3):
	for i in range(len(t[j])):
		t[j][i]/=((i+1)**div)

n=range(100)
scatter(n, t[0], label="Aleatorio") 
scatter(n, t[1], label="MC", color='#FF0000') 
scatter(n, t[2], label="PC", color='#00FF00') 

barra= ''
if (div>0): barra='/n'
if (div>1): barra+= '^'+str(div)

legend()

ylabel('Tiempo (Ciclos)'+barra)
xlim(0,101)
ylim(0,max(t[2][10:100]))
xlabel('Tam. Entrada')
title('Tiempo de Computo')
grid(True)
savefig(sys.argv[2]+".png")
