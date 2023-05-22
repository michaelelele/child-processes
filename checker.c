#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int dividend, divisor;

    if(argc != 2){ //Checks if invalid number of arguments was sent
        fprintf(stderr, "Checker Error: Invalid number of arguments.\n");
        exit(1);
    }

    divisor = atoi(argv[0]);
    dividend = atoi(argv[1]); // initializes divident and divisor with values

    if(dividend % divisor == 0){ //Returns 1 if dividend is divisible by divisor and 0 if it doesn't
        return 1;
    }
    else{
        return 0;
    }

}
