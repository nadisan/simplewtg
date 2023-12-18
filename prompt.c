#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
        char *buffer = "$ ";
        size_t input;
        char *line = NULL;
        size_t len = 0;
        char *argv[100];
        unsigned int i = 0;
        pid_t child_pid;
        int status;


        while (1)
        {
                write(STDOUT_FILENO, buffer, 3);
                input = getline(&line, &len, stdin);
                if (input == -1)
                {       write(1, "\n", 1);
                        free(line);
                        break;
                }
                argv[0] = strtok(line, " \n");
                while (argv[i])
                {       i++;
                        argv[i] = strtok(NULL, " \n");
                }
                child_pid = fork();
                if (child_pid == -1)
                 {
                    perror("Error:");
                    return (1);
                }
                if (child_pid == 0)
                {
                    if (execve(argv[0], argv, NULL) == -1)
                    {
                        perror("Error:");
                    }
                }
                else
                {
                    wait(&status);
                }
        }
        printf("After execve\n");
        return (0);
}
