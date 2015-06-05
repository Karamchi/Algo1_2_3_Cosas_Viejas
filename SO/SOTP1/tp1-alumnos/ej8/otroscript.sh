n=2
c=1
m=2
q=2
rm TP.out
rm WT.out

for j in {1..10}
do
	for i in {1..4}
	do
		./../simusched probando.tsk $i $c $m SchedRR $q $q $q $q > RR_$i$c$m$q
		./../simusched probando.tsk $i $c $m SchedRR2 $q $q $q $q > RR2_$i$c$m$q	
		python calcularTP.py probando.tsk RR_$i$c$m$q >> TP.out
		python calcularWT.py probando.tsk RR_$i$c$m$q >> WT.out
		python calcularTP.py probando.tsk RR2_$i$c$m$q >> TP.out
		python calcularWT.py probando.tsk RR2_$i$c$m$q >> WT.out
	done
	for i in {1..4}
	do
		./../simusched probando.tsk $n $i $m SchedRR $q $q $q $q > RR_$n$i$m$q
		./../simusched probando.tsk $n $i $m SchedRR2 $q $q $q $q > RR2_$n$i$m$q
		python calcularTP.py probando.tsk RR_$n$i$m$q >> TP.out
		python calcularWT.py probando.tsk RR_$n$i$m$q >> WT.out
		python calcularTP.py probando.tsk RR2_$n$i$m$q >> TP.out
		python calcularWT.py probando.tsk RR2_$n$i$m$q >> WT.out
	done
	for i in {1..4}
	do
		./../simusched probando.tsk $n $c $i SchedRR $q $q $q $q > RR_$n$c$i$q
		./../simusched probando.tsk $n $c $i SchedRR2 $q $q $q $q > RR2_$n$c$i$q
		python calcularTP.py probando.tsk RR_$n$c$i$q >> TP.out
		python calcularWT.py probando.tsk RR_$n$c$i$q >> WT.out
		python calcularTP.py probando.tsk RR2_$n$c$i$q >> TP.out
		python calcularWT.py probando.tsk RR2_$n$c$i$q >> WT.out
	done
	for i in {1..4}
	do
		./../simusched probando.tsk $n $c $m SchedRR $i $i $i $i > RR_$n$c$m$i
		./../simusched probando.tsk $n $c $m SchedRR2 $i $i $i $i > RR2_$n$c$m$i
		python calcularTP.py probando.tsk RR_$n$c$m$i >> TP.out
		python calcularWT.py probando.tsk RR_$n$c$m$i >> WT.out
		python calcularTP.py probando.tsk RR2_$n$c$m$i >> TP.out
		python calcularWT.py probando.tsk RR2_$n$c$m$i >> WT.out
	done
done
rm RR*
