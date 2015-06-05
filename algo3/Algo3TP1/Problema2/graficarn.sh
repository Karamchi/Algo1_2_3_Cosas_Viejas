for n in {0..3}
do
	for l in {0..1}
	do
		python graficarn.py $n $l E2-$n$l
	done
done
#rm Tiempo*
