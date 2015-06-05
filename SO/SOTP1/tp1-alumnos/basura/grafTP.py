from pylab import *


labels=['Num cores','Costo de cambio de contexto','Costo de migracion','Quantum']
for i in range(4):
	values = []
	values2 = []

	read_file = open('TP.out')

	numline=0
	for line in read_file:
		if numline/4==i:
			values.append(float(line))
		if numline/4==4+i:
			values2.append(float(line))
		numline+=1
	

	x=range(1,5,1)
	xlabel(labels[i]+' (ciclos)', color= '#072b57')
	ylabel('Throughput (procesos/ciclo)', color= '#072b57')
	title('Quantum', color='#072b57')

	plot(x,values,label="RR")
	plot(x,values2,label="RR2")
	legend(loc=2)
	ylim(0,0.12)
	plt.xticks(np.arange(min(x), max(x)+1, 1.0))
	grid(True)
	savefig(str(i)+'.png', dpi=300, format='png')
