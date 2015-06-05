loads=[0,0,0,0,0]
exits=[0,0,0,0,0,0,0,0,0,0]
spans=[23,29,35,41,12,15,10,20,15,25]
for j in range(4):
	for i in range(1,5,1):
		nom=[2,1,2,2]
		nom[j]=i
		noms=nom[0]*1000+nom[1]*100+nom[2]*10+nom[3]
		for k in range(2):
			suma=0
			if not k: read_file = open("RR_"+str(noms))
			else: read_file = open("RR2_"+str(noms))
			for line in read_file:
				tipo=line.split()[0]
				if tipo=="EXIT":
					tarea=int(line.split()[2])
					exits[tarea]=int(line.split()[1])
			for i in range(10):
				suma+=exits[i]-spans[i]
			if not k: print suma/10.0,'\t',
			else: print suma/10.0
