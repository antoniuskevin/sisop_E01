#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int total=0;
static int status;

void *prima(void *args){
	int* angka1;
	int angka;
	int stat=0;
	int i;
	angka1=(int*)malloc(sizeof(int));
	angka1 = (int*)args;
	angka=(*angka1);
	for(i=2;i<=(angka);i++){
		if((angka%i==0)&&(i!=angka)){
			stat=1;
			printf("%d adalah bilangan bukan prima\n",angka);
			break;
		}
	}
	if (stat==0){
		total+=angka;
		printf("%d adalah bilangan prima\n",angka);
	}
}
int jumlah_prima(){
	int angka;
	int i;
	int *conf;
	int stat;
	int threadnum=0;	
	printf("Masukkan angka: ");
	scanf("%d",&angka);
	pthread_t thread [angka+2];
	//jumlah prima dari 2 sampai angka-1
       	for(i=2;i<angka;i++){
		conf=(int*)malloc(sizeof(int));
		*conf=i;
	       	stat=pthread_create(&thread[i], NULL, &prima, (void*)conf);
	/*	if(stat){
			printf("thread creation error\n");
		}
	else{
			printf("thread %d created\n",i);
			threadnum+=1;
		}*/
	}
	for(i=2;i<angka;i++){
		pthread_join(thread[i],NULL);
	}
	printf("Jumlah anda: %d\n",total);
//	printf("threadnum:%d\n",threadnum);
	return 0;
}



void *thread_01(void *filenames)
{
    //printf("thread 1 started\n");
    FILE *f1, *f2;
    char line[101];
    char **filenames_ = (char **) filenames;
    f1 = fopen(filenames_[0], "r");
    f2 = fopen(filenames_[1], "a");
    while (fgets(line, 100, f1))
    {
        fprintf(f2, "%s", line);
	    //printf("file1 > file2 : %s", line);
    }
    fclose(f1);
    fclose(f2);

    status = 1;
    //printf("thread 1 stopped\n");
}

void *thread_02(void *filenames)
{
    //printf("thread 2 started\n");
    char line[101];
    FILE *f2, *f3;
    char **filenames_ = (char **) filenames;
    f2 = fopen(filenames_[1], "r+");
    f3 = fopen(filenames_[2], "a");
    //printf("while thread 2 started\n");
    //printf("thread 2 status = %d\n", status);
    while (!(!fgets(line, 100, f2) && status == 1))
    {
        //printf("Loop status = %d\n", status);
        fprintf(f3, "%s", line);
        line[0] = '\0';
        //printf("file2 > file3 : %s", line);
    }
    //printf("thread 2 stopped\n");
    fclose(f2);
    fclose(f3);
}

int salin_file()
{
    pthread_t threadid[2];
    
    char **filenames = (char **) malloc(sizeof(char*) * 3);
    int i;
    FILE *fcheck;
    for (i = 0; i < 3; i++)
    {
        printf("Masukkan nama file %d : ", i);
        filenames[i] = (char *) malloc(sizeof(char)*101);
        scanf("%s", filenames[i]);
        if (access(filenames[i], F_OK) != 0)
        {
            printf("File can not be accessed!\n");
            exit(EXIT_FAILURE);
        }
        fflush(stdin);
    }

    status = -1;
    pthread_create(&threadid[0], NULL, thread_01, (void *)filenames);
    pthread_create(&threadid[1], NULL, thread_02, (void *)filenames);
    pthread_join(threadid[0], NULL);
    //status = 1;
    //printf("main status = %d\n", status);
    pthread_join(threadid[1], NULL);

    free(filenames);
    
    return 0;
}
int main(){
	int pilihan;
	printf("Praktikum Modul 2\n");
	printf("Pilih salah satu dari menu dibawah:\n");
	printf("1. Menjumlahkan semua bilangan prima kurang dari input\n");
	printf("2. Menyalin isi file ke sebuah file, kemudian disalin lagi ke file lain\n");
	printf("Pilihan anda:");
	scanf("%d",&pilihan);
	if(pilihan==1){
		jumlah_prima();
	}
	else if(pilihan==2){
		salin_file();
	}
	else{
		return 0;
	}
	main();
}		







