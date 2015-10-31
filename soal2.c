#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int total=0;

void *run(void *args){
	int* angka1;
	int angka;
	int stat=0;
	int i;
	angka1=(int*)malloc(sizeof(int));
	angka1 = (int*)args;
	angka=(*angka1);
	for(i=1;i<=(angka);i++){
		if (angka==1){
			break;
		}
		if((angka%i==0&&(i!=1&&i!=angka))){
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
	pthread_t thread [angka+1];
	//jumlah prima dari 1 sampai angka
       	for(i=1;i<=angka;i++){
		conf=(int*)malloc(sizeof(int));
		*conf=i;
	       	stat=pthread_create(&thread[i], NULL, &run, (void*)conf);
		if(stat){
			printf("error\n");
		}
		else{
			printf("created\n");
			threadnum+=1;
		}
	}
	for(i=1;i<=angka;i++){
		pthread_join(thread[i],NULL);
	}
	printf("Jumlah anda: %d\n",total);
	printf("threadnum:%d\n",threadnum);
	return 0;
}
