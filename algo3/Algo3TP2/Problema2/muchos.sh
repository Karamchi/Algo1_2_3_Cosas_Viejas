rm -f Tiempo
#for s in {0..200..40}
#do
#	echo $s
#	for n in {2..100}
#	do
#		for i in {1..10}
#		do
#			python generarTest.py $n 20 $s > test1
#			for j in {1..10}
#			do
#				./ej2 < test1 > res
#			done
#		done
#	done
#	mv Tiempo Tiempon_$s
#done

for n in {40..200..40}
do
	echo $n
	for s in {2..200..2}
	do
		for i in {1..10}
		do
			python generarTest.py $n 20 $s > test1
			for j in {1..10}
			do
				./ej2 < test1 > res
			done
		done
	done
	mv Tiempo Tiempos_$n
done

rm test1
rm res
bash graficar.sh