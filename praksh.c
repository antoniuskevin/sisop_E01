/* PRAKSH   : PRAKtikum SHell */

/****************************
Terdapat beberapa fase ketika shell berjalan:
1. Inisialisasi:
    - Memuat konfigurasi awal sebelum menjalankan perintah
2. Interpret:
    - Melaksankan perintah yang telah diketik
3. Terminate:
    - free-kan alokasi memori

Loop dasar:
1. Read
    - membaca perintah
2. Parse
    - memisahkan argumen dan option
3. Execute
*****************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PRAKSH_BUFFER_SIZE 1024
#define PRAKSH_DELIM_PARSE " \0\n\t"

char *ReadCommand()
{  
    int index = 0,
        bufferSize = PRAKSH_BUFFER_SIZE;
    char *bufferCommand;
    char c;

    bufferCommand = malloc(sizeof(char) * bufferSize);

    while(1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            bufferCommand[index] = '\0';
            break;
        }
        else
        {
            bufferCommand[index] = c;
        }
        index++;

        if (index >= bufferSize) 
        {
            bufferSize += PRAKSH_BUFFER_SIZE;
            bufferCommand = realloc(bufferCommand, bufferSize);
            if (!bufferCommand)
            {
                fprintf(stderr, "praksh: realloc error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return bufferCommand;
}

char** Parsing(char *command)
{
    char *delim;
    int bufferSize = PRAKSH_BUFFER_SIZE;
    char **args = malloc(sizeof(char*) * bufferSize);
    char *token;
    int index = 0;

    delim = PRAKSH_DELIM_PARSE;

    token = strtok(command, delim);
    
    while (token != NULL)
    {
        args[index] = token;
        if (index >= bufferSize)
        {
            args = realloc(args, bufferSize);
            if (!args)
            {
                fprintf(stderr, "praksh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, delim);
        index += 1;
    }
    args[++index] = NULL;
    return args;
}

int Execute(char **args)
{
    pid_t procId, wpid;
    int status;

    procId = fork();
    if (procId < 0)
    {
        fprintf(stderr, "praksh: forking: error\n");
        exit(EXIT_FAILURE);
    }
    else if (procId == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "praksh: execvp: error\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        do {
            wpid = waitpid(procId, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

void main_loop()
{
    char* line;
    char** args;
    int status;
    do
    {
        printf("praksh >> ");
        line = ReadCommand();
        args = Parsing(line);
        status = Execute(args);
    } while(status);
    free(line);
    free(args);
}

int main()
{
    main_loop();
    
    exit(EXIT_SUCCESS);
    return 0;
}
