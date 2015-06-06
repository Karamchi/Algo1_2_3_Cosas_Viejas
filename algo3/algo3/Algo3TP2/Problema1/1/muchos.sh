rm Tiempo
for n in {1..100}
do
	echo $n
	for i in {1..10}
	do
		python generarTest.py $n > test1
		for i in {1..10}
		do
			./ej1 < test1 > res
		done
	done
done
rm test1
rm res
bash graficar.sh
