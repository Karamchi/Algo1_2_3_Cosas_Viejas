from pylab import *

read_file=open("in")

x=range(2,10)
y=[]

for line in read_file:
	y.append(float(line.split()[2]))

for i in range(len(y)):
	y[i]/=(2**((i+1)**2))

plot(x, y, '--', label="Peor caso") 

legend()
ylabel('Tiempo (Ciclos)/2^(n^2)')
#ylim(0,0.12)
yscale('log')
xlabel('Tamano del tablero (n)')
title('Tiempo de Computo')
grid(True)
show()
