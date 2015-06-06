import random
import sys

n=int(sys.argv[1])
f=int(sys.argv[2])
print n
s=0
for i in range(n):
	C=random.randint(0,10000)
	print s,f,C
	s=random.randint(0,f)
	f=random.randint(s,f)

