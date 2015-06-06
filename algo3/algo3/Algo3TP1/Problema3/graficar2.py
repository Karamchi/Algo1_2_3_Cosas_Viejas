from pylab import *
from math import *

values = []

# read_file = open('Tiempo')
f = open('sarasa3')



data = {}

n = 2
k = i = 0
for line in f:
	# Esta en segundos con 6 digitos de precision.
	value = float(line.replace("\n", ""))
	value = int(value * (1000 * 1000)) # Y ahora esta en microsecs
	if not n in data: data[n] = {}
	if not k in data[n]: data[n][k] = []
	# print n, k, i
	# print l[n]
	# print l[n][k]
	data[n][k].append(int(value))
	i+=1
	if i >= 100:
		k+=1
		i=0
	if k > n*n:
		n+=1
		k=0

def getValues(mode):
	ret = []
	# n = [0..8] y k = 0
	if mode == 0:
		for n in range(2, 10):
			l = data[n][0]
			# value = (sum(l) / len(l)) / (n**8)
			# value = (sum(l) / len(l)) / (2**(n**1.4))
			value = (sum(l) / len(l)) / (1)
			print sum(l) / len(l)
			ret.append(value)
	# n = [0..8] y 0<k<n
	elif mode == 1:
		for n in range(2, 10):
			value = 0
			for k in range(1, n+1):
				l = data[n][k]
				value += (sum(l) / len(l)) / (2**(n**log(4, math.e)))
			
			ret.append(value)

	# n = [0..8] y 0<k<n
	elif mode == 2:
		for n in range(2, 10):
			value = 0
			for k in range(n, n*n+1):
				l = data[n][k]
				value += (sum(l) / len(l)) / (2**(n*n))
			
			ret.append(value)
	else:
		pass

	return ret

g1 = getValues(0)

t=list(range(2, 10))

yscale('symlog')
# xscale('log')

plot(t, g1, '--', label="Aleatorio") 
#plot(t, g2, label="Mejor Caso")
#plot(t, g3, label="Adyacentes") 
#plot(t, g4, label="Piramide")

legend()
ylabel('Tiempo')
#ylim(0,0.12)
#yscale('log')
xlabel('N')
title('Tiempo de Computo')
grid(True)
show()
