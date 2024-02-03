# OSAssignment1
Assignment description :

Task:

Write a C program that simulates a parallel task execution scenario using process forking. The program should create a specified number of child processes, each performing a unique task. The parent process should wait for all child processes to complete before displaying the final result.

Requirements:

    Your program should take an integer input n from the user, where n represents the number of child processes to be created. n should be less than 5.
    Each child process should perform a different task, such as computing the factorial of a number, finding prime numbers in a range, or any computationally intensive operation.
    The parent process should display a message before creating (forking) the child processes.
    Each child process should print its own identifier (PID) and the task it is performing.
    After completing their tasks, each child process should print a completion message.
    The parent process should wait for all child processes to finish before displaying a final message.

Additional Considerations:

    Use the fork() system call to create child processes.
    You may use other relevant system calls or functions as needed (e.g., wait() , exit() ).
    Ensure proper error handling for system calls.
    Design the code to guarantee the creation of exactly n children, ensuring that each child executes its intended task. Properly manage the process creation to avoid any unintended duplication or omission of child processes.
