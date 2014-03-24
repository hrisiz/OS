//--------------------------------------------
// NAME: Hristiqn Zarkov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #2
// FILE NAME: HM2v1.c
// FILE PURPOSE:
// реализира прост команден интерпретатор shell
//---------------------------------------------
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

char** parse_cmdline ( const char * cmdline );
//--------------------------------------------
// FUNCTION: parse_cmdline
// връща масив от C-стрингове
// PARAMETERS:
// const char * cmdline - line ot stdin
//----------------------------------------------
int main()
{
        char* line=NULL;
        size_t len = 1;
        char** arg;
        while (getline(&line,&len,stdin) != -1)
        {
                arg = parse_cmdline(line);
                int pid = fork();
                if (pid == 0)
                {
                        execv(arg[0],arg);
                        perror(arg[0]);
                        return -1;
                }
                else if(pid < 0)
                {
                        perror("Fork");
                }
                else
                {
                        int status;
                        waitpid(pid,&status,0);
                }
                
        }
        int counter = 0;
        while(arg[counter] != NULL){
	    free(arg[counter]);
	    counter++;
	}
	free(arg[counter]);
	free(arg);
        return 0;
}
char** parse_cmdline (const char * cmdline )
{
        char** the_array = (char **)malloc(sizeof(char*));
        int symbol_counter = 0;
        int array_counter = 0;
        int help_string_counter = 0;
        char next_symbol = cmdline[symbol_counter];
        while(next_symbol != '\n')
        {
                if(next_symbol == ' ')
                {
                        help_string_counter = 0;
                        array_counter++;
                        the_array = (char **)realloc(the_array,(array_counter+1)*sizeof(char*));
                }
                else
                {
                        the_array[array_counter] = (char *) realloc(the_array[array_counter],(help_string_counter+1)*sizeof(char));
                        the_array[array_counter][help_string_counter] = next_symbol;
                        help_string_counter++;
                }
                symbol_counter++;
                next_symbol = cmdline[symbol_counter];
        }
        the_array = (char **)realloc(the_array,(array_counter+2)*sizeof(char*));
        the_array[array_counter+1] = NULL;
        return the_array;
}
