#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int brashno = 1000;
int masa[4];
pthread_mutex_t lock;

void* Mama(){
    int position = 0;
    while(brashno) {
        int mama_get_brashno = rand() % 100 + 1;
        if(mama_get_brashno > brashno){
            mama_get_brashno = brashno;
        }
        brashno -= mama_get_brashno;
        while(masa[position] == 1){
            int wtime = rand() % 100 + 1;
            usleep(wtime*1000);
        }
        printf("MAMA PRAI PASTI4KA!\n");
        usleep(mama_get_brashno*1000);
        pthread_mutex_lock(&lock);
        masa[position] = 1;
        pthread_mutex_unlock(&lock);
        if(position == 3) {
            position = 0;
        } else {
            position++;
        }
    }
}

void* Ivan(){
    int position = 0;
    while(brashno){
        while(masa[position] == 0) {
            int wtime = rand() % 100 + 1;
            usleep(wtime*1000);
        }
        pthread_mutex_lock(&lock);
        masa[position] =0;
        pthread_mutex_unlock(&lock);
        printf("IVAN4O LAPA PASTI4KAAA!\n");
        if(position == 3) {
            position = 0;
        } else {
            position++;
        }
    }
}

int main(){
    pthread_mutex_init(&lock,NULL);
    pthread_t thread[2];
    pthread_create(&thread[0],NULL,Mama,NULL);
    pthread_create(&thread[1],NULL,Ivan,NULL);
    pthread_join(thread[1],NULL);
    pthread_mutex_destroy(&lock);
    return 0;
} 
