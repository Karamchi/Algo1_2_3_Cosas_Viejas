import sys
entrada=open(sys.argv[1])
nl=0
zMatH=[]
zMatV=[]
error=[]
for line in entrada:
	if (nl==0):
		n,m,s=map(int,line.split())
	elif (nl==1):
		ih,iv,bh,bv=map(int,line.split())
	elif nl%2==0:
		zMatH.append(map(int,line.split()))
	elif nl%2==1:
		zMatV.append(map(int,line.split()))
	nl+=1

res=open(sys.argv[2])
i=[]
j=[]
nl=0
for line in res:
	if nl>0:
		i.append(int(line.split()[0]))
		j.append(int(line.split()[1]))
	else: sob=int(line)
	nl+=1

if [i[0],j[0]] <> [ih,iv]: 
	error.append("Error, no empieza en el inicial")

for c in range(1,len(i)):
	mov = [i[c]-i[c-1],j[c]-j[c-1]]
	print mov,c,
	if mov == [1,0]: z=zMatV[i[c-1]-1][j[c-1]-1]
	elif mov == [-1,0]: z=zMatV[i[c]-1][j[c]-1]
	elif mov == [0,1]: z=zMatH[i[c-1]-1][j[c-1]-1]
	elif mov == [0,-1]: z=zMatV[i[c]-1][j[c]-1]
	else:
		error.append("Error, movimiento invalido")
		break
	if z>s:
		s-=(z-s)
		if s==0:
			error.append("Error, murieron todos")
			break

if [i[len(i)-1],j[len(i)-1]] <> [bh,bv]:
	error.append("Error, no termina en el bunker")
elif s<>sob:
	error.append("Error, la cantidad de sobrevivientes no es correcta")
else: error.append("El camino es posible")
print error[0]
