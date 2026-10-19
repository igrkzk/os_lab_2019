#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s seed array_size\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Child process - выполняем sequential_min_max
        char *args[] = {"./sequential_min_max", argv[1], argv[2], NULL};
        execv("./sequential_min_max", args);
        
        // Если exec вернул управление, произошла ошибка
        printf("Exec failed!\n");
        return 1;
    } else {
        // Parent process - ждем завершения дочернего
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        
        return 0;
    }
}