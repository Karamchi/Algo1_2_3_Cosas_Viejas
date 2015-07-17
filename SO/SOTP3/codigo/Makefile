MPICC   = mpicc
MPIEXEC = mpiexec
CFLAGS += -Wall

EJECUTABLE = tp3

.PHONY : all new clean run

all : $(EJECUTABLE) run

tp3 : tp3.c srv.c
	$(MPICC) $(CFLAGS) -o tp3 tp3.c srv.c

run : tp3
	$(MPIEXEC) -np 14 ./$(EJECUTABLE) '.' 2 50 50 '1' 1 0 10 '2' 5 0 100 '3' 8 80 0 '4' 1 50 1 >/dev/null

clean :
	rm -f $(EJECUTABLE)

new : clean all
