for n in {0..8}
do
	for  (( k=0; k<=$n; k++ )) 
	do
		i=$n"x"$k
		echo $i
		./tests/TR $n $k '0' > tests/test$i;
	done
done
