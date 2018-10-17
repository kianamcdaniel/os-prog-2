/*			Lab 2 			*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

main()
{
char *path, *argv[20], buf[80], n, *p;         //path is name of in/out file

    int m, status, inword, continu;
    
    int fin, fout, input, output;
    
    int args[10] = {0};
    
    int count, numPipes;
    pid_t pid;
    
    int pipe1[2];
    int pipe2[2];
    
    while(1) {

        inword = 0;
        p = buf;
        m = 0;
        continu=0;
        
        count = 0;
        pipe = 0;
        pid = 0;
        
        fin = 0;
        fout = 0;

        printf( "\nshhh> ");

        while ( ( n = getchar() ) != '\n'  || continu ) {
            if ( n ==  ' ' ) {
                if ( inword ) {
                    inword = 0;
                    *p++ = 0;
                }
            }
            else if ( n == '\n' )
                continu = 0;
            else if ( n == '\\' && !inword )
                continu = 1;
            else {
                if ( !inword ) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                }
                else
                    *p++ = n;
            }
        }

        *p++ = 0;
        argv[m] = 0;
        
        if ( strcmp(argv[0],"exit") == 0 )
            exit (0);
        
        while (argv[count] != 0){             //while not at end of command line
            if (strcmp(argv[count], "|") == 0){     //if arg is a pipe
                argv[count] = 0;                    //set loc. of pipe to 0
                args[pipes + 1] = count + 1;        //save loc. of next arg
                numPipes++;
            }
            else if (strcmp(argv[count], "<") == 0){    //if arg is redirect in
                path = strdup(argv[count + 1]);   //next arg will be in file name
                argv[count] = 0;
                argv[count + 1] = 0;
                fin = 1;
            }
            else if (strcmp(argv[count], ">") == 0){
                path = strdup(argv[count + 1]);
                argv[count] = 0;
                argv[count + 1] = 0;
                fout = 1;
            }
            else{
                args[count] = count;
            }
            count++;
        }
        
        for (int i = 0; i <= pipes; i++){
            if(i < pipes){
                pipe(pipe2);
            }
            
            pid = fork();
            
            if (pid < 0){
                printf("ERROR");
                exit(1);
            }
            else if (pid == 0){
                if((index == 0) && (fin == 1)){
                    input = open(path, O_RDONLY, 0600);
                    dup2(input, 0);
                    close(input);
                }
            
                if ((index == pipes) && (fout == 1)){
                    output = open(path, O_WRONLY | O_CREAT, 0600);
                    dup2(output, 1);
                    close(output);
                }
                
                execvp(argv[args[index]], &argv[args[index]]);
            }
            else{
                close(pipe1[0]);
                close(pipe1[1]);
            }
            pipe1[0] = pipe2[0];
            pipe1[1] = pipe2[1];
        }
        wait(&status);
    }
}

