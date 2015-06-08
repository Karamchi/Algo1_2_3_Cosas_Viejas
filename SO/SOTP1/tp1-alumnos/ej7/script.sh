rm *.out
for n in {1..3}
do
	echo $n
	for m in {1..20}
	do
		for j in {1..10}
		do
			./../simusched probando.tsk $n 1 2 SchedRR $m $m $m > probando$n$m
		#	python graphsched.py probando$n$m
		#	python graph_cores.py probando$n$m
			python calcularWT.py probando.tsk probando$n$m >> WT.out
			python calcularTP.py probando.tsk probando$n$m >> TP.out
		done
	done
done
# mv *.png res
mv probando.tsk res
rm probando*
mv res/probando.tsk ../ej7
