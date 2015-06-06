rm -f Tiempo
rm -f Mins
rm -f Tam
for m in {0..3}
do
	for n in {1000..100000..1000} 
	do
		echo $n
		python generarTest.py $n $m > test1;
		for j in {1..10}
		do
			./Ej2 < test1 > res
		done
	done
	mv Tiempo Tiempo$m
done
bash graficarn.sh
bash testsm.sh
rm res
rm test1
