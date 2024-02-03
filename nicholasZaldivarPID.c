#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#define M_PI 3.14159265358979323846


/* Nicholas Zaldivar
 * Panther ID: 4884728
 *
 * C program that simulates a parallel task execution scenario using process forking.
 * The program creates a specified number of child processes, each performing a unique task.
 * The parent process then waits for all child processes to complete before displaying the final result.
*/

//Function that computes a factorial of a number (Child 1)
int fact(int n){
    long long int result = 1;
    if (n == 0 || n == 1) { //Check if factorial is 0 or 1 to skip processing
        printf("Factorial of %d is equal to 1", n);
    } else if (n < 0) { //Catch to prevent user from inputting a negative
        printf("Error factorial cannot be negative");
        return 0;
    } else {
        for (int i = n; i > 0; i--) { //For loop to create the factorial formula
            result *= i;
        }
    }
    printf("Factorial Process is complete\n"); //Announcing process has completed
    return result;
}

//Checking if a number is a prime number (Child 2)
bool isPrime(int n){
    if (n <= 1){
        return false;
    }
    for (int i = 2; i * i <= n; i++){ //For loop to create prime number formula
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

//Finding Prime numbers and ordering them into an array (Child 2)
int *findPrime(int lowerLimit, int upperLimit, int *primeCount){ //Using * to assign memory locations in order to be able to return an array
    *primeCount = 0;
    for (int i = lowerLimit; i <= upperLimit; i++){ //Formula to count prime numbers in range
        if (isPrime(i)){
            (*primeCount)++;
        }
    }
    
int *primeMemory = (int*)malloc((*primeCount) * sizeof(int)); //Array memory declaration
    if (primeMemory == NULL) {exit(1);} //Catch if memory allocation fails

    int index = 0;
    for (int i = lowerLimit; i <= upperLimit; i++){ //For loop to index prime numbers into an array
        if (isPrime(i)){
            primeMemory[index++] = i;
        }
    }
    printf("Prime Number Process is Complete\n"); //Announcing process has completed
    return primeMemory;
}

//Finding the Hypotenuse of a triangle using pythagorean theorem given a and b (Child 3)
double pythagoreanTheorem(int a, int b){
    double c = (pow(a,2)) + (pow(b,2)); //Pythogrean Theorem Formula
    c = sqrt(c);
    printf("Pythagorean Theorem Process is Complete\n"); //Announcing process has completed
    return c;
}

//Finding the area of a circle using pi (Child 4)
double areaCircle(int r){
    double area = (pow(r, 2)); //Area of circle formula
    area *= M_PI; //M_PI has been defined on line 6 as '3.14159265358979323846'
    printf("Area of a Circle Process is Complete\n"); //Announcing process has completed
        return area;
}

int main() {
    int userInput, n, primeCount;
    printf("Please pick a number between 1 and 4 to create child processes\n");
    scanf("%d", &n); //Your program should take an integer input n from the user, where n represents the number of child processes to be created. n should be less than 5.
    if (n <= 0 || n >= 5){ //If or to prevent user from inputting outside of required child processes
        printf("Invalid, number must be between 1 and 4.");
        return 0;
    }
    printf("Parent process, (PID %d) is now creating %d number of child processes.\n", getpid(), n);
    for (int i = 0; i < n; i++) {
        pid_t pid = fork(); //Use the fork() system call to create child processes.
        if (pid < 0) { //Checking for a failed fork (<0)
            fprintf(stderr, "Fork Failure\n"); //Ensure proper error handling for system calls.
            exit(1);
        } else if (pid == 0) { //Checking for child pid (=0)
            printf("%d: My PID is %d and my parent's PID is %d\n", i+1, getpid(), getppid());
            switch (i) { //Switch case allows child processes to run different commands
                case 0:
                    //Child 1
                    printf("1: Child 1 is computing the factorial of 6\n");
                    long long int childResult1 = fact(6); //Running Factorial method
                    printf("1: Factorial Result: %lld\n", childResult1); //Result is printed
                    printf("1: Child 1 is ending it's task\n");
                    _exit(0); //System call to gracefully end process
                case 1:
                    //Child 2
                    printf("2: Child 2 is finding the prime numbers in a range of 4 and 6\n");
                    int *childResult2 = findPrime(4, 16, &primeCount); //Running Prime method
                    printf("2: Prime Numbers: ");
                        for (int i = 0; i < primeCount; i++){ //For loop to print out array created in the Prime method
                            printf("%d ", childResult2[i]); //Result is printed
                        }
                    printf("\n");
                    printf("2: Child 2 is ending it's task\n");
                    _exit(0); //System call to gracefully end process
                case 2:
                    //Child 3
                    printf("3: Child 3 is finding the length of c using Pythagorean Theorem\n");
                    double childResult3 = pythagoreanTheorem(5.00, 8.00); //Running pythagorean method
                    printf("3: Hypotenuse: %f\n", childResult3); //Result is printed
                    printf("3: Child 3 is ending it's task\n");
                    _exit(0); //System call to gracefully end process
                case 3:
                    //Child 4
                    printf("4: Child 4 is finding the area of a circle with a radius of size 4\n");
                    double childResult4 = areaCircle(4); //Running area of circle method
                    printf("4: Area of a Circle: %f\n", childResult4); //Result is printed
                    printf("4: Child 4 is ending it's task\n");
                    _exit(0); //System call to gracefully end process
            }
        }
    }
            //Parent
            printf("P: This is the parent process. PID = %d\n", getpid());
            wait(4);
            //This will wait for all child processes to finish
            printf("P: All Children Processes have finished\n");
          
    return 0;
}
