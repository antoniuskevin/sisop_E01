#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include  <stdlib.h>

int total=0;

void *run(void *args){
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
int main(){
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
	       	stat=pthread_create(&thread[i], NULL, &run, (void*)conf);
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
