import sys
import random

n=int(sys.argv[1])
modo=int(sys.argv[2])
modos=[0,n*(n-1)/2,random.randint(0,n*(n-1)/2), n]
m=modos[modo]
print n,m

links=[]
if modo<3:
	links=[]
	for i in range(1,n+1):
		for j in range(i+1,n+1):
			links.append([i,j])

	random.shuffle(links)

	for i in range(m):
		u,v=links[i]
		print u,v

else:
	for i in range(1,n):
		print i,i+1
	print n,1
