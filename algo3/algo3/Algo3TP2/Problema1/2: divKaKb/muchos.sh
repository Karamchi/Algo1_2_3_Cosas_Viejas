rm Tiempo
for m in {0..2}
do
	for n in {1..100}
	do
		echo $n
		for i in {1..10}
		do
			python generarTest.py $n $m > test1
			for i in {1..10}
			do
				./ej1 < test1 > res
			done
		done
	done
	mv Tiempo Tiempo_$m
done
rm test1
rm res
bash graficar.sh
