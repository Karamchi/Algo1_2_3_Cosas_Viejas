./../simusched probando.tsk 1 0 1 SchedFixed > probandoF
./../simusched probando.tsk 1 0 1 SchedDynamic > probandoD
python graphsched.py probandoD
python graphsched.py probandoF
rm probandoD
rm probandoF
