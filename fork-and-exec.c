#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

static void child() {
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("I'm child! my pid is %d.\n", getpid());
    fflush(stdout);
    execve("/bin/echo", args, NULL);
    err(EXIT_FAILURE, "exec() failed");
}

static void parent(pid_t pid_c) {
    printf("I'm parent! my pid is %d and the pid of my child is %d.\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(void) {
    pid_t ret;
    ret = fork();
    if (ret == -1) {
        err(EXIT_FAILURE, "fork() failed");
    } else if (ret == 0) {
        child();
    } else {
        parent(ret);
    }
    // 도달할 수 없을 것.
    err(EXIT_FAILURE, "shouldn't reach here");
}