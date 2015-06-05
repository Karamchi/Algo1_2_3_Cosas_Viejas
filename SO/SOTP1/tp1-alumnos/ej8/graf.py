import sys
import math
from pylab import *

values=[[],[],[],[]]
values2=[[],[],[],[]]
proms=[[],[]]
std=[[],[]]

read_file = open('WT.out')
i=int(sys.argv[1])
labels=['Num Cores', 'Costo de cambio de contexto','Costo de migracion','Quantum']
units=['',' (ciclos)',' (ciclos)',' (ciclos)']
numline=0

for line in read_file:
	if (numline%32)/8==i:
		if (numline%2==0):
			values[numline/2%4].append(float(line))
		else:
			values2[(numline-1)/2%4].append(float(line))
	numline+=1
	
for j in range(4):
    proms[0].append(mean(values[j]))
    proms[1].append(mean(values2[j]))
    variance = map(lambda x: (x - proms[0][j])**2, values[j])
    std[0].append(math.sqrt(average(variance)))
    variance = map(lambda x: (x - proms[1][j])**2, values2[j])
    std[1].append(math.sqrt(average(variance)))



x=range(1,5,1)
xlabel(labels[i]+units[i], color= '#072b57')
ylabel('Waiting time (ciclos)', color= '#072b57')
title(labels[i], color='#072b57')

plot(x,proms[0],label="RR",color= '#072b57')
plot(x,proms[1],label="RR2",color= '#FF0000')
prup=[]
prdn=[]
for i in range(4):
    prup.append(proms[0][i]+std[0][i])
    prdn.append(proms[0][i]-std[0][i])
plot(x,prup,':',color= '#072b57',label="RR varianza")
plot(x,prdn,':',color= '#072b57',label="RR2 varianza")
for i in range(4):
    prup[i]=(proms[1][i]+std[1][i])
    prdn[i]=(proms[1][i]-std[1][i])
plot(x,prup,':',color= '#FF0000')
plot(x,prdn,':',color= '#FF0000')

#legend()
legend(loc=2)
#ylim(0,250)
plt.xticks(np.arange(min(x), max(x)+1, 1.0))
grid(True)
show()
