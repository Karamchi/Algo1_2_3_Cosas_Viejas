rm -f Tiempo
rm -f Mins
rm -f Tam
for n in {20000..100000..20000} 
do
	for m in {1000..100000..1000}
	do
		echo $m
		python generarTestm.py $n $m > test1
		for j in {1..10}
		do
			./Ej2 < test1 > res
		done
	done
	mv Tiempo Tiempom_$n
done
python graficarm.sh "Min"
rm res
rm test1
