import random
import sys

n=int(sys.argv[1])
modo=int(sys.argv[2])
print n
if (modo==0):
	for i in range(n):
		c = random.randint(0,(n*2))
		print c,
		f = random.randint(0,(n*2)+1)
		s = random.randint(0,f)  
		print s,f
elif (modo==1):
	c = random.randint(0,(n*2))
	f = random.randint(0,(n*2)+1)  
	s = random.randint(0,f)
	for i in range(n):
		print c,s,f
elif (modo==2):
	s=0
	for i in range(n):
		c = random.randint(0,(n*2))  
		print c,s,
		f = random.randint(0,(2)+s+1)  
		print f
		s = f
else:
	for i in range(n):
		c = n*2-i
		s = i
		f = c
		print c,s,f
