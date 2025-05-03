#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipefd[2];  // File descriptors for the pipe
    pid_t pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {  // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  
        // Child Process: Executes "findstr .c" (Windows equivalent of grep)
        close(pipefd[1]);  // Close unused write end of the pipe

        // Redirect pipe read end to standard input
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  // Close pipe read end after redirection

        // Execute "findstr .c" to filter for .c files (Windows equivalent of grep)
        execlp("findstr", "findstr", ".c", NULL);
        perror("execlp findstr");
        exit(EXIT_FAILURE);
    } else {  
        // Parent Process: Executes "dir /b"
        close(pipefd[0]);  // Close unused read end of the pipe

        // Redirect pipe write end to standard output
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);  // Close pipe write end after redirection

        // Execute "dir /b" to list files (Windows equivalent of ls)
        execlp("cmd", "cmd", "/c", "dir /b", NULL);
        perror("execlp dir");
        exit(EXIT_FAILURE);
    }

    return 0;
}
