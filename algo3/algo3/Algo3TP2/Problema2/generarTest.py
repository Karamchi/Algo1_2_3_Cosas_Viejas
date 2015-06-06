import sys
import random
n=int(sys.argv[1])
m=int(sys.argv[2])
s=int(sys.argv[3])
print n,m,s
ih=random.randint(1,n)
iv=random.randint(1,m)
bh=random.randint(1,n)
bv=random.randint(1,m)
print ih,iv,bh,bv

for i in range(n-1):
	for i in range(m-1):
		print random.randint(0,100),
	print '\n',
	for i in range(m):
		print random.randint(0,100),
	print '\n',
for i in range(m-1):
	print random.randint(0,100),
print '\n',
