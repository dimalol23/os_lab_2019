#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        execl("./sequential_min_max", "./sequential_min_max", "seed", "arraysize", NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else{
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)){
            printf("Program sequential_min_max has been executed with code %d\n", WIFEXITED(status));
        }
    }
    return EXIT_FAILURE;
}