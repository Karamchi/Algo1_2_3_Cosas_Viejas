rm -f Tiempo
for n in {20..100..20}
do
	echo $n
	for m in {1..150}
	do
		echo $m
		for i in {1..10}
		do
			python generarTestm.py $n $m > test1
			for i in {1..10}
			do
				./ej3 < test1 > res
			done
		done
	done
	mv Tiempo Tiempo$n
done
rm test1
rm res
bash graficarm.sh
