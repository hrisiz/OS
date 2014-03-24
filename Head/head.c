//--------------------------------------------
// NAME: Hristiqn Zarkov
// CLASS: XIб
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: head.c
// FILE PURPOSE:
// 4ete ot daden fail purvite 10 reda i gi pokazva.
//---------------------------------------------

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define READ_ROWS 10

int write_file(int fd);

int main(int ARGC,char *ARGV[]) {
	int files_counter;
	if(ARGC == 1){
		write_file(STDIN_FILENO);
	}
	for(files_counter = 1;files_counter < ARGC;files_counter++){
		if(ARGV[files_counter][0] == '-'){
			write_file(STDIN_FILENO);
		}else{
			if(ARGC > 2){
				char file_name_p[100];
				strcpy(file_name_p,"==> ");
				strcat(file_name_p,ARGV[files_counter]);
				strcat(file_name_p," <==\n");
				if (write(STDOUT_FILENO,file_name_p,strlen(file_name_p)) < 0){
					perror("File name write problem");
				}
			}
			int fd = open(ARGV[files_counter],O_RDONLY);
			if(fd < 0){
				char error[100];
				strcpy(error,"head : cannot open ’");
				strcat(error,ARGV[files_counter]);
				strcat(error,"’ for reading");
				perror(error);
			}else{
				write_file(fd);
			}
		}
	}
	return 0;
}

int write_file(int fd){
	int status = 10;
	char buffer;
	int lines = 0;
	while(status != 0 && lines < READ_ROWS){
		if((status = read(fd,&buffer,1)) < 0){
			perror("Read problem");
			return -1;
		}
		if(buffer == '\n'){
			lines++;
		}
		status = write(STDOUT_FILENO,&buffer,1);
		if(status < 0){
			perror("Write problem");
			return -2;
		}
	}
}
