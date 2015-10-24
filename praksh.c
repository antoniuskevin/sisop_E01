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

#define PRAKSH_BUFFER_SIZE 1024
#define PRAKSH_DELIM_PARSE "\0\n\t "

char *read_command()
{   
    int index,
        bufferSize = PRAKSH_BUFFER_SIZE;
    char *bufferCommand;
    char c;

    bufferCommand = malloc(sizeof(char) * 1024);
    while(1)
    {
        c = getchar();
        
        if (c != '\0' || c != '\n')
        {
            bufferCommand[index] = c;
            index++;
            if (index >= bufferSize)
            {
                bufferCommand = realloc(bufferCommand, bufferSize);
                if (!bufferCommand)
                {
                    fprintf(stderr, "praksh: allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            bufferCommand[index] = '\0';
            break;
        }
    }
    return bufferCommand;
}

char** parsing(char *command)
{
    char *delim;
    int bufferSize = 128;
    char **args = malloc(sizeof(char) * bufferSize);
    char *token;
    int index = 0;

    strcpy(delim, PRAKSH_DELIM_PARSE);
    
    token = strtok(command, delim);

    while (token != NULL)
    {
        args[index] = token;
        token = strtok(NULL, delim);
        if (index >= bufferSize)
        {
            args = realloc(args, bufferSize);
            if (!args)
            {
                fprintf(stderr, "praksh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return args;
}

void execute(char **args)
{
    pid_t procId;
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
            // fprintf(
        }
    }

}

void main_loop()
{
}

int main()
{
    main_loop();
    
    exit(EXIT_SUCCESS);
    return 0;
}
