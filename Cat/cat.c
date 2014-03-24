#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

char *read_text;
pthread_mutex_t mutex_lock;
int result_counter = 0;
void *write_read_text(void *YouCantWorkWithoutME){
	int write_status = 1;
	int is_end = 0;
	while(is_end != 1){
		pthread_mutex_lock(&mutex_lock);
			printf("xaxa");
			write_status = write(STDOUT_FILENO,read_text,strlen(read_text));
			if(read_text[strlen(read_text)] == '\0'){
				is_end = 1;
				free(read_text);
			}
			result_counter = 0;
		pthread_mutex_unlock(&mutex_lock);
	}
	pthread_exit(NULL);
}	
void *read_file(void *file_name){
	int fd = open((char*)file_name,O_RDONLY);
	if(fd < 0){
		perror("Open Problem");
		pthread_exit((void *)-1);
	}
	int read_status = 1;
	read_text = (char *)malloc(sizeof(char));
	int buffer_size = 20;
	char *buffer = (char *)malloc(buffer_size*sizeof(char));
	//printf("\n\nbuffer:%d\n\n",(int)strlen(buffer));
	while(read_status != 0){
		read_status = read(fd,buffer,buffer_size);
		//printf("\n\nbuffer:%d\n\n",(int)strlen(buffer));
		if(read_status < 0){
			perror("Read Problem");
			pthread_exit((void *) -2);
		}else{
			//printf("%d\n",(int)strlen(read_text));
			pthread_mutex_lock(&mutex_lock);
				//printf("reasult_coiunter:%d",(int)(result_counter*sizeof(char)));
				//read_text = (char *)realloc(read_text,result_counter*sizeof(char));
				int i;
				for(i = 0; i < read_status; i++){
					read_text = (char *)realloc(read_text,(result_counter+(i+1))*sizeof(char));
					read_text[result_counter+i] = buffer[i];
					//printf("buffer_count:%d\nread_status:%d\nlength:%d\ni:%d\n\n",(int)strlen(buffer),read_status,result_counter,i);
				}
				result_counter += buffer_size;
				//printf("\n");
			pthread_mutex_unlock(&mutex_lock);
		}
	}
	pthread_exit(NULL);
}
int main(int argc,char* argv[]){
	int i;
	//pthread_t thread_id[(argc-1)*2];
	pthread_t thread_id[2];
	pthread_create(thread_id,NULL,read_file,(void *)argv[1]);
	pthread_create(thread_id,NULL,write_read_text,NULL);
	pthread_join(thread_id[0],NULL);
	/*for(i = 1; i < argc;i++){ 
		pthread_create(thread_id,NULL,read_file,(void *)argv[i]);
		pthread_join(thread_id[(i*2-2)],NULL);
		pthread_create(thread_id,NULL,write_read_text,NULL);
		pthread_join(thread_id[(i*2-1)],NULL);
		//printf("%s\n",read_text);
	}*/
	pthread_exit(NULL);
}
