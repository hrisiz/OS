#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define ARRAY_SIZE 20000

int main(){
	int i;
	int arr[ARRAY_SIZE];

	for(i = 0; i < ARRAY_SIZE; i++){
		arr[i] = i % 255;
	}


	pid_t pid[2];
	pid[0] = fork();
	if(pid[0] < 0){
		perror("fork error");	
	}	
	else if(pid[0] == 0){
		int sum = 0;
		for(i = 0; i < ARRAY_SIZE/2; i++){
			sum += arr[i];
		}
		return sum/(ARRAY_SIZE/2);
	}
	else{
		pid[1] = fork();
		if(pid[1] < 0){
		perror("fork error");	
		}	
		else if(pid[1] == 0){
			int sum = 0;
			for(i = ARRAY_SIZE/2;i < ARRAY_SIZE; i++){
				sum += arr[i];
			}
			return sum/(ARRAY_SIZE/2);
		}else{
			int average[2];
			int status[2];
			waitpid(pid[0], &status[0], 0);
			waitpid(pid[1], &status[1], 0);
			average[0] = WEXITSTATUS(status[0]);
			average[1] = WEXITSTATUS(status[1]);
			printf("Average is %d\n", (average[0]+average[1])/2);
		}

	}
}
