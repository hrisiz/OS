#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
char *substr(char *string,int start){
	int i;
	char *result = (char *) malloc((strlen(string)-start)*sizeof(char));
	for(i = 0; i < (strlen(string)-start); i++){
		result[i] = string[i+start];
	}
	return result;
}

char *union_arrays(char *result ,char *string2){
	int i;
	int result_start_count = strlen(result);
	for(i = 0; i < strlen(string2); i++){
		result[result_start_count+i] = string2[i];
	}
	return result;
}
int main(){

	char **string = (char **)malloc(2*sizeof(char*));
	int i;
	for(i = 0;i< 2; i++){
		string = (char **) realloc(string,(i+1)*sizeof(char*));
		string[i] = (char *) malloc(sizeof(char));
		string[i][0] = 'a';
	}
	/*char *array_for_delete = (char *)malloc(5*sizeof(char));
	char *save_array = string + 4;
	array_for_delete = string;*/
	//printf("Start:%d\n",(int)strlen(string));
	//free(array_for_delete);
	//string = save_array;
	/*int *xax;
	int *xaxa;
	xax = xaxa;
	free(xaxa);*/
	free(string[0]);
	string += 1;
	//printf("END:%d\n",(int)strlen(string));
	for(i = 0; i < 1; i++){
		printf("%c\n",string[i][0]);
	}
	return 0;
}
