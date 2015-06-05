import sys
read_file=open(sys.argv[1])
nl=0
for line in read_file:
	if (nl==0):
		n,m,s=line.split()
		print n, m, int(sys.argv[2])
	else:
		print(line),
	nl+=1
