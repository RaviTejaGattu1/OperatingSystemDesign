#include <stdio.h>      // Standard input-output header
#include <signal.h>     // Signal handling header
#include <unistd.h>     // POSIX API for various system calls, including sleep
#include <stdlib.h>     // Standard library header for exit function
#include <sys/types.h> // Header for various data types used in system calls
#include <sys/wait.h>   // Header for wait-related system calls

volatile int DEBUG = 0; // Volatile variable for debug mode flag
int counter = 1;         // Counter variable for tracking iterations

// Signal handler for toggling debug mode
void sigintdebugtoggle(int signum) {
    if (signum == SIGINT) { // Check if SIGINT signal is received
        DEBUG = !DEBUG; // Toggle debug mode flag
        if (DEBUG) {
            printf("Switched ON Debug Mode\n"); // Print debug mode enabled message
        } else {
            printf("Switched OFF Debug Mode\n"); // Print debug mode disabled message
        }
    }
}

// Signal handler for graceful exit
void sigusr1exit(int signum) {
    if (signum == SIGUSR1) { // Check if SIGUSR1 signal is received
        printf("Graceful exit using SIGUSR1.\n"); // Print message for graceful exit
        exit(0); // Exit the program gracefully
    }
}

int main() {
    signal(SIGINT, sigintdebugtoggle); // Register signal handler for SIGINT
    signal(SIGUSR1, sigusr1exit);      // Register signal handler for SIGUSR1

    while (1) { // Infinite loop
        if (DEBUG) { // Check if debug mode is enabled
            printf("Number of iteration: %d\n", counter); // Print current iteration number
        }
        counter++; // Increment the counter
        sleep(2);  // Sleep for 2 seconds
    }

    return 0; // Return 0 to indicate successful execution (never reached in this infinite loop)
}
