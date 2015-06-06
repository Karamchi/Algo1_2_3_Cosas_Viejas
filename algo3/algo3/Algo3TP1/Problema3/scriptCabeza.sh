rm Tiempo
for n in {0..8}
do
	for  (( k=0; k<=$n; k++ )) 
	do
		i=$n"x"$k
		echo $i
		for j in {1..2}
		do
			./Ej3 < tests/test$i > res
		done
	done
done
rm res
rm *.o
