#include <signal.h>
#include <stdio.h>

static void example_handler(int signum);

int main(void) {
		int n;
		int sig_id[] = { SIGINT, SIGTSTP, SIGTERM, SIGUSR1, SIGUSR2 };

		for ( n = 0; n < 5; n++) {
				if(signal(sig_id[n], example_handler ) == SIG_ERR) {
						printf( "\n signal() system call returned SIG_ERR.");
						return -1;
				}
		}

		while(1) {
				pause();
		}
		return 0;
}

static void example_handler (int signum) {
		switch(signum) {
				case SIGINT: printf( "\n SIG_INT was caught !!!" ); break;
				case SIGTSTP: printf( "\n SIG_TSTP was caught !!!" ); break;
				case SIGTERM: printf( "\n SIG_TERM was caught !!!" ); break;
				case SIGUSR1: printf( "\n SIG_USR1 was caught !!!" ); break;
				case SIGUSR2: printf( "\n SIG_USR2 was caught !!!" ); break;
		}
	//	fflush();
}
