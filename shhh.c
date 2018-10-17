/*			Lab 2 			*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

main()
{
    char *file, *argv[20], buf[80], n, *p;

    int m, status, inword, continu;
    
    int fin, fout;
    
    int args[20] = {0};
    
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
        numPipes = 0;
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
        
        //while not at end of command line
        while (argv[count] != 0){
            if (strcmp(argv[count], "|") == 0){               //if arg is a pipe
                argv[count] = 0;                         //set loc. of pipe to 0
                args[numPipes + 1] = count + 1;          //save loc. of next arg
                numPipes++;
            }
            else if (strcmp(argv[count], "<") == 0){               //redirect in
                file = strdup(argv[count + 1]);                 //copy file name
                argv[count] = 0;
                fin = 1;
            }
            else if (strcmp(argv[count], ">") == 0){              //redirect out
                file = strdup(argv[count + 1]);                 //copy file name
                argv[count] = 0;
                argv[count + 1] = 0;
                fout = 1;
            }
            else{
                args[count] = count;
            }
            count++;
        }
        
        for (int i = 0; i <= numPipes; i++){
            if ((numPipes > 0) && (i != numPipes)){
                pipe(pipe2);
            }
            
            pid = fork();
            
            if (pid < 0){
                printf("ERROR");
                exit(1);
            }
            else if (pid == 0){
                if((i == 0) && (fin == 1)){
                    int input = open(file, O_RDONLY, 0600);
                    dup2(input, 0);                            //read from input
                    close(input);                                  //close input
                }
            
                if ((i == numPipes) && (fout == 1)){
                    int output = open(file, O_WRONLY | O_CREAT, 0600);
                    dup2(output, 1);                           //write to output
                    close(output);                                //close output
                }
                
                if (numPipes > 0){
                    if (i == 0){
                    //close std out, std out reassigned to std out of 2nd pipe
                        close(1);
                        dup(pipe2[1]);
                        close(pipe2[1]);
                        close(pipe2[0]);
                    }
                    else if (i < numPipes){
                    //close std in, std in reassigned to std in of 1st pipe
                        close(0);
                        dup(pipe1[0]);
                        close(pipe1[0]);
                        close(pipe1[1]);
                    //close std out, std out reassigned to std out of 2nd pipe
                        close(1);
                        dup(pipe2[1]);
                        close(pipe2[0]);
                        close(pipe2[1]);
                    }
                    else {
                    //close std in, std in reassiged to std in of 1st pipe
                        close(0);
                        dup(pipe1[0]);
                        close(pipe1[0]);
                        close(pipe1[1]);
                    }
                }
                execvp(argv[args[i]], &argv[args[i]]);         //execute command
            }
            else{
                close(pipe1[0]);                          //close 1st pipe input
                close(pipe1[1]);                         //close 1st pipe output
            }
            pipe1[0] = pipe2[0];                            //now input of pipe
            pipe1[1] = pipe2[1];
        }
        
        if (strcmp(argv[0], "exit") == 0){
            exit(0);
        }
        
        for(int i = 0; i < 20; i++){
            argv[i] = 0;
        }
        
        wait(&status);
    }
}


