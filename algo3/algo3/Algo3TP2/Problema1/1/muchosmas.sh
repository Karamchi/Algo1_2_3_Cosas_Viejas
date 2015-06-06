rm Tiempo
for n in {1..20}
do
	echo $n
	for  (( ka=0; ka<=$n; ka++ )) 
	do
		for  (( kb=0; kb<=$n; kb++ )) 
		do
			python generarTest.py $n $ka $kb > test1
			for i in {1..10}
			do
				./ej1 < test1 > res
			done
		done
	done
done
rm test1
rm res
