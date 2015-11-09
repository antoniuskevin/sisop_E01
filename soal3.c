#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int status;

void *thread_01()
{
    //printf("thread 1 started\n");
    FILE *f1, *f2;
    char line[101];
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "a");
    while (fgets(line, 100, f1))
    {
        fprintf(f2, "%s", line);
	//printf("file1 > file2 : %s", line);
    }
    fclose(f1);
    fclose(f2);
    //printf("thread 1 stopped\n");
}

void *thread_02()
{
    //printf("thread 2 started\n");
    char line[101];
    FILE *f2, *f3;
    f2 = fopen("file2.txt", "r+");
    f3 = fopen("file3.txt", "a");
    //printf("while thread 2 started\n");
    //printf("thread 2 status = %d\n", status);
    while (!(!fgets(line, 100, f2) && status == 1))
    {
        //printf("Loop status = %d\n", status);
        fprintf(f3, "%s", line);
	//printf("file2 > file3 : %s", line);
    }
    //printf("thread 2 stopped\n");
    fclose(f2);
    fclose(f3);
}

int main()
{
    pthread_t threadid[2];

    status = -1;
    pthread_create(&threadid[0], NULL, thread_01, NULL);
    pthread_create(&threadid[1], NULL, thread_02, NULL);
    pthread_join(threadid[0], NULL);
    status = 1;
    //printf("main status = %d\n", status);
    pthread_join(threadid[1], NULL);
    return 0;
}
