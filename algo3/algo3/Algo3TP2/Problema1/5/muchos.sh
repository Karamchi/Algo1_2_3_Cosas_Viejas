rm -f Tiempo
for ka in {0..100..20}
do
	echo $ka
	for n in {1..1000..10}
	do
		for i in {1..10}
		do
			python generarTest.py $n $ka 20 > test1
			for j in {1..10}
			do
				./ej1 < test1 > res
			done
		done
	done
	mv Tiempo Tiempon_$ka
done

#for n in {0..100..20}
#do
#	echo $n
#	for ka in {1..100}
#	do
#		for i in {1..10}
#		do
#			python generarTest.py $n $ka 20 > test1
#			for j in {1..10}
#			do
#				./ej1 < test1 > res
#			done
#		done
#	done
#	mv Tiempo Tiempos_$n
#done

rm test1
rm res
bash graficar.sh
