#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sigalrm_handler(int sig) {
    printf("Alarm Signal: %d\n", sig);
}

int main() {
    int i=0, ret;
    struct sigaction sa_new, sa_old;
    
    memset(&sa_new, 0, sizeof(struct sigaction));
    memset(&sa_old, 0, sizeof(struct sigaction));
    sa_new.sa_handler = sigalrm_handler;
    ret = sigaction(SIGALRM, &sa_new, &sa_old);
    if(ret < 0) {
        perror("sigaction() failed");
        _exit(1);
    }

    alarm(7); // send SIGALRM signal after given seconds to current process
    while(i < 10) {
        printf("running: %d\n", ++i);
        sleep(1);
    }
    return 0;
}
