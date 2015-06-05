values = []

read_file = open('probando')

for line in read_file:
	values = (line.split(" "))
	if (values[0]=="CPU") or (values[0]=="LOAD") or (values[0]=="EXIT"):
		values[2]=str(int(values[2])/10)
		if (values[0]=="LOAD"):
			values[2]=values[2]+"\n"
	for i in range(len(values)):
		print values[i],
#	if len(values)==3:
#		print "\n"
