#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static long status;

void *thread_01()
{
    FILE *f1, *f2;
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "a");
    while (1)
    {
        char line[101];
        if (fgets(line, 100, f1) != NULL)
        {
            fprintf(f2, "%s", line);
        }
        else
            break;
    }
    fclose(f1);
    fclose(f2);
}

void *thread_02()
{
    char line[101];
    FILE *f2, *f3;
    f2 = fopen("file2.txt", "r");
    f3 = fopen("file3.txt", "a");
    while (fgets(line, 100, f2) != NULL && status != 1)
    {
        fprintf(f3, "%s\n", line);
    }
}

int main()
{
    pthread_t threadid[2];

    status = -1;
    pthread_create(&threadid[0], NULL, thread_01, NULL);
    pthread_create(&threadid[1], NULL, thread_02, NULL);
    pthread_join(threadid[0], NULL);
    status = 1;
    return 0;
}
