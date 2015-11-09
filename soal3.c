#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_01()
{
    printf("thread 1 started\n");
    FILE *f1, *f2;
    char *line;
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "a");
    while (fscanf(f1, "%[^\n]s", line) != EOF)
    {
        fprintf(f2, "%s\n", line);
        memset(line, NULL, sizeof(line));
        printf("%s\n", line);
    }
    fclose(f1);
    fclose(f2);
    printf("thread 2 stopped\n");
}

void *thread_02(void *vStatus)
{
    printf("thread 2 started\n");
    long iStatus = (long) vStatus;
    char *line;
    FILE *f2, *f3;
    f2 = fopen("file2.txt", "r");
    f3 = fopen("file3.txt", "a");
    while (fscanf(f2, "%[^\n]s", line) != EOF && iStatus != 1)
    {
        //printf("vStatus = %ld, iStatus = %ld\n", vStatus, iStatus);
        fprintf(f3, "%s\n", line);
        iStatus = (long) vStatus;
    }
    printf("thread 2 stopped\n");
}

int main()
{
    pthread_t threadid[2];
    static long status;

    status = -1;
    pthread_create(&threadid[0], NULL, thread_01, NULL);
    pthread_create(&threadid[1], NULL, thread_02, (void *) status);
    pthread_join(threadid[0], NULL);
    status = 1;
    return 0;
}
