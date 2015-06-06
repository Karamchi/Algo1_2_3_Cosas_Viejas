import random
import sys
n=int(sys.argv[1])
modo=int(sys.argv[2])

km=random.randint(1,n)
kb=random.randint(1,n)
if (modo==1):
	km=0
	kb=0
elif (modo==2):
	km=n
	kb=n

print n, km, kb

for i in range(n):
		print random.randint(1,10),
		print random.randint(1,10),
		print random.randint(1,10)
