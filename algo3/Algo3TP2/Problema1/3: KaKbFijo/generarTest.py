import random
import sys
n=int(sys.argv[1])
km=int(sys.argv[2])
kb=int(sys.argv[3])

print n, km, kb
for i in range(n):
	print random.randint(1,10),
	print random.randint(1,10),
	print random.randint(1,10)
