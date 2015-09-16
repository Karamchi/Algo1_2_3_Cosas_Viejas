import sys
import random

n=int(sys.argv[1])
m=int(sys.argv[2])

print n,m
links=[]
for i in range(1,n+1):
	for j in range(i+1,n+1):
		links.append([i,j])

random.shuffle(links)

for i in range(m):
	u,v=links[i]
	print u,v
