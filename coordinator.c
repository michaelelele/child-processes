#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int divisor, dividend;
    pid_t pid;

    if (argc != 6) { //Sends error if invalid number of arguments sent.
        fprintf(stderr, "Coordinator Error: Invalid number of arguments.\n");
        exit(1);
    }

    divisor = atoi(argv[1]);

    for(int i = 2; i < argc; i++){
        dividend = atoi(argv[i]);

        pid = fork();

        if(pid == -1){ //Send error if fork fails
            fprintf(stderr, "Coordinator Error: Fork failed.\n");
        }
        else if(pid == 0){ // Creates child process
            printf("Checker process [%d]: Starting.\n",getpid());
            execlp("checker", argv[1], argv[i]); //Calls and passes arguments to chekcer program
        }
        else{
            printf("Coordinator: forked process with ID %d.\n", pid); //Prints that child process was created and is waiting for it's result
            printf("Coordinator: waiting for process [%d].\n", pid);
            int status;
            wait(&status); //Waits
            int result = WEXITSTATUS(status); // receives result from checker program
            if(result == 1){ //Prints if dividend is divisble by divisor
                printf("Checker Process [%d]: %d *IS* divisible by %d\n", pid, dividend, divisor);
            }
            else{ //Prints if dividend is not divisble by divisor
                printf("Checker Process [%d]: %d *IS NOT* divisible by %d\n", pid, dividend, divisor);
            }
            printf("Checker process [%d]: Returning %d\n", pid, result); //prints what child process returned
            printf("Coordinator: child process %d returned %d.\n", pid, result); //again prints what child process returned
        }

    }

    printf("Coordinator: exiting.\n"); //Prints exit line



}