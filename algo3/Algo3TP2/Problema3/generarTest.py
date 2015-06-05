import random
import sys
n=int(sys.argv[1])
modo=int(sys.argv[2])
if (modo<2):
	m=random.randint(0,n*(n-1)/2)*(1-modo)
	C=random.randint(1,10)*(1-modo)
	print n, m, C
	for i in range(m):

		a=random.randint(1,n)
		b=random.randint(1,n)
		while (b==a):
			b=random.randint(1,n)
		print a,b,
		print random.randint(1,10)
else:
	m=n*(n-1)/2
	C=n**2*20
	print n, m, C
	for i in range(1,n+1):
		for j in range(1,n+1):
			if (i <> j):
				print i,j,
				print random.randint(1,10)
