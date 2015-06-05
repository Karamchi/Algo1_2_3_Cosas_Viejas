import sys
import math
from pylab import *

values=[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
values2=[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
values3=[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
proms=[[],[],[]]
std=[[],[],[]]

read_file = open('TP.out')
numline=0

for line in read_file:
	if (numline/200==0):
		values[(numline%200)/10].append(float(line))
	elif (numline/200==1):
		values2[(numline%200)/10].append(float(line))
	else:
		values3[(numline%200)/10].append(float(line))
	numline+=1
	
for j in range(20):
    proms[0].append(mean(values[j]))
    proms[1].append(mean(values2[j]))
    proms[2].append(mean(values3[j]))
    variance = map(lambda x: (x - proms[0][j])**2, values[j])
    std[0].append(math.sqrt(average(variance)))
    variance = map(lambda x: (x - proms[1][j])**2, values2[j])
    std[1].append(math.sqrt(average(variance)))
    variance = map(lambda x: (x - proms[2][j])**2, values3[j])
    std[2].append(math.sqrt(average(variance)))



x=range(1,21,1)
xlabel('Quantum (ciclos)', color= '#072b57')
ylabel('Throughput (tareas/ciclo)', color= '#072b57')
title('Quantum', color='#072b57')

plot(x,proms[0],label="1 core",color= '#072b57')
plot(x,proms[1],label="2 cores",color= '#FF0000')
plot(x,proms[2],label="3 cores",color= '#00CC00')
prup=[]
prdn=[]
for i in range(20):
    prup.append(proms[0][i]+std[0][i])
    prdn.append(proms[0][i]-std[0][i])
plot(x,prup,':',color= '#072b57',label="1 core varianza")
plot(x,prdn,':',color= '#072b57')
for i in range(20):
    prup[i]=(proms[1][i]+std[1][i])
    prdn[i]=(proms[1][i]-std[1][i])
plot(x,prup,':',color= '#FF0000',label="2 cores varianza")
plot(x,prdn,':',color= '#FF0000')
for i in range(20):
    prup[i]=(proms[2][i]+std[2][i])
    prdn[i]=(proms[2][i]-std[2][i])
plot(x,prup,':',color= '#00CC00',label="3 cores varianza")
plot(x,prdn,':',color= '#00CC00')

#legend()
legend(loc=2)
ylim(0,0.15)
plt.xticks(np.arange(min(x), max(x)+1, 1.0))
grid(True)
show()
