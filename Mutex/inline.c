#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define ARRAY_SIZE 100000
int sum;

pthread_mutex_t lock;

void* halfSum(void * start){
	int *arr = start;
	int i;
  int localsum;
	for(i = 0; i < ARRAY_SIZE/2; i++){
		localsum += arr[i];
	}
  
  pthread_mutex_lock(&lock);
  sum += localsum;
  pthread_mutex_unlock(&lock);
}

int main(){
	int arr[ARRAY_SIZE];
	int i;
	for(i = 0; i < ARRAY_SIZE; i++){
		arr[i] = 2;
	}

	pthread_mutex_init(&lock,NULL);
	pthread_t thread_number[2];
	pthread_create(&thread_number[0],NULL,halfSum,arr);
	pthread_create(&thread_number[1],NULL,halfSum,&arr[ARRAY_SIZE/2]);

	pthread_join(thread_number[0],NULL);
	pthread_join(thread_number[1],NULL);

	pthread_mutex_destroy(&lock);
  printf("%d\n",sum);
	return 0;
}
