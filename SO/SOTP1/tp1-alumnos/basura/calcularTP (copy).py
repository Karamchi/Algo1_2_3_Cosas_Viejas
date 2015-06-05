exits=[0,0,0,0,0,0,0,0,0,0]
for j in range(4):
	for i in range(1,5,1):
		for k in range(2):
			nom=[2,1,2,2]
			nom[j]=i
			noms=nom[0]*1000+nom[1]*100+nom[2]*10+nom[3]
			if not k: read_file = open("RR_"+str(noms))
			else: read_file = open("RR2_"+str(noms))
			suma=0
			for line in read_file:
				tipo=line.split()[0]
				if tipo=="EXIT":
					tarea=int(line.split()[2])
					exits[tarea]=int(line.split()[1])
			if not k: print 10.0/max(exits),'\t',
			else: print 10.0/max(exits)
