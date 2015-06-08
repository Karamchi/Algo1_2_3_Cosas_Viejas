import sys
read_src = open (sys.argv[1])
spans=[]
n=0
for line in read_src:
	if line.split()[0]=="TaskCPU":
		spans.append(int(line.split()[1]))
	elif line.split()[0]=="TaskBatch":
		spans.append(int(line.split()[1])+int(line.split()[2]))
	n+=1

exits=[0]*n
read_file = open(sys.argv[2])
for line in read_file:
	tipo=line.split()[0]
	if tipo=="EXIT":
		tarea=int(line.split()[2])
		exits[tarea]=int(line.split()[1])

print float(n)/max(exits)
