for s in {1..400}
do
	python modificarTest.py test1 $s > test2
	for i in {1..10}
	do
		./ej2 < test2 > res
	done
done

