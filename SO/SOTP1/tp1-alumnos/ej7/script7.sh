rm Tiempo
for m in {1..13}
do
	echo $m
	./../simusched probando.tsk 1 1 2 SchedRR $m > probando$m
	python graphsched.py probando$m
	python graph_cores.py probando$m
done
mv probando.tsk res
mv *.png res
rm probando*
mv res/probando.tsk ../ej7
