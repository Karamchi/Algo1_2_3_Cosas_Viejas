//Se pide un programa justiciero en C que ejecute el comando pasado por parámetro, no permitiéndole a este enviar una signal a otro proceso mediante kill. En caso que el comando especificado intente enviar la signal, se debe abortar su ejecución y mostrar el mensaje: “Se ha hecho justicia!”. Por ejemplo: 
//$ ./justiciero kill -9 28988
//Se ha hecho justicia!
//Sugerencia: Use el programa launch.c + ptraces (slides 24 de la presentacin) como base.


#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char* argv[]) {
	int status;
	pid_t child;

	if (argc <= 1) {
		fprintf(stderr, "Uso: %s commando [argumentos ...]\n", argv[0]);
		exit(1);
	}

	/* Fork en dos procesos */
	child = fork();
	if (child == -1) { perror("ERROR fork"); return 1; }
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		/* S'olo se ejecuta en el Hijo */
		execvp(argv[1], argv+1);
		/* Si vuelve de exec() hubo un error */
		perror("ERROR child exec(...)"); exit(1);
	} else {

		//ptrace(PTRACE_ATTACH, child); //Attachea al child

		/* S'olo se ejecuta en el Padre */
		while(1) {

			int sysno = ptrace(PTRACE_PEEKUSER, child, 8*ORIG_RAX, NULL); //Devuelve rax de child (eax no lo reconoce)
			if (sysno==9) {
				ptrace(PTRACE_KILL, child, NULL, NULL);
				printf("Se ha hecho justicia!\n");
			}
	                ptrace(PTRACE_SYSCALL,child, NULL, NULL);

			if (wait(&status) < 0) break;
			if (WIFEXITED(status)) break; /* Proceso terminado */
		}
	}
	return 0;
}
