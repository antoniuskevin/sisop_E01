#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int status;

void *thread_01()
{
    printf("thread 1 started\n");
    FILE *f1, *f2;
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "a");
    while (1)
    {
        char line[101];
        if (fgets(line, 100, f1) != NULL)
        {
            fprintf(f2, "%s", line);
	    printf("file1 > file2 : %s", line);
        }
        else
            break;
    }
    fclose(f1);
    fclose(f2);
    printf("thread 1 stopped\n");
}

void *thread_02()
{
    printf("thread 2 started\n");
    char line[101];
    FILE *f2, *f3;
    f2 = fopen("file2.txt", "r+");   // masalah!!!
    f3 = fopen("file3.txt", "a");
    printf("while thread 2 started\n");
    printf("thread 2 status = %d\n", status);
    while (!feof(f2) && status != 1)
    {
        fgets(line, 100, f2);
        printf("Loop status = %d\n", status);
        fprintf(f3, "%s", line);
	printf("file2 > file3 : %s", line);
    }
    printf("thread 2 stopped\n");
    fclose(f2);
    fclose(f3);
}

int main()
{
    pthread_t threadid1, threadid2;

    status = -1;
    pthread_create(&threadid1, NULL, thread_01, NULL);
    pthread_create(&threadid2, NULL, thread_02, NULL);
    pthread_join(threadid1, NULL);
    status = 1;
    printf("main status = %d\n", status);
    pthread_join(threadid2, NULL);
    return 0;
}
