#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
// common signal handler for multiple signals
void sig_handler(int sig) {
    printf("Signal received: %d\n", sig);
    switch (sig) {
    case SIGINT:
        printf("SIGINT caught!\n");
        break;
    case SIGTERM:
        printf("SIGTERM caught!\n");
        break;
    case SIGALRM:
        printf("SIGALRM caught!\n");
        break;
    }
}


// seprate signal handler for SIGSEG
void sigsegv_handler(int sig) {
 printf("SIGSEGV caught...\n");
 _exit(0);
 }

int main() {
	struct sigaction sa;
	int ret,i=0;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sig_handler;
	ret = sigaction(SIGINT, &sa,NULL);
	if(ret< 0) {
		perror("sigaction() failed");
	_exit(1);
}
alarm(8); //send SIGALRM to current process after 8 seconds
while(i < 20) {
printf("running: %d\n", ++i);
        sleep(1);
    }

    int *p = NULL;
    *p = 1234; // This will cause segmentation fault.
    
    printf("bye!\n"); // Will not execute, because program exit from sigsegv handler.
    return 0;
}

	
