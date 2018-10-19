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
    
    int lp[2];
    int rp[2];
    
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
        
        //pre-processing
        while (argv[count] != 0){
            if (strcmp(argv[count], "|") == 0){
                argv[count] = 0;
                args[numPipes + 1] = count + 1;
                numPipes++;
            }
            else if (strcmp(argv[count], "<") == 0){
                file = strdup(argv[count + 1]);
                argv[count] = 0;
                fin = 1;
            }
            else if (strcmp(argv[count], ">") == 0){
                file = strdup(argv[count + 1]);
                argv[count] = 0;
                fout = 1;
            }
            else{
                args[count] = count;
            }
            count++;
        }
        
        for (int i = 0; i <= numPipes; i++){
            if ((numPipes > 0) && (i != numPipes)){
                pipe(rp);
            }
            
            pid = fork();
            
            if (pid < 0){
                printf("ERROR");
                exit(1);
            }
            else if (pid == 0){
                if((i == 0) && (fin == 1)){
                    int input = open(file, O_RDONLY, 0600);
                    close(0);
                    dup(input);
                    close(input);
                }
            
                if ((i == numPipes) && (fout == 1)){
                    int output = open(file, O_WRONLY | O_CREAT, 0600);
                    close(0);
                    dup(input);
                    close(input);
                }
                
                if(numPipes >0){
                    if(index == 0){
                        close(1);
                        dup(rp[1]);
                        close(rp[1]);
                        close(rp[0]);
                    }
                    if(index < numPipes){
                        close(0);
                        dup(lp[0]);
                        close(lp[0]);
                        close(lp[1]);
                        
                        close(1);
                        dup(rp[1]);
                        close(rp[1]);
                        close(rp[0]);
                    }
                    else{
                        close(0);
                        dup(lp[0]);
                        close(lp[0]);
                        close(lp[1]);
                    }
                }
                execvp(argv[args[i]], &argv[args[i]]);
            }
            else{
                close(lp[0]);
                close(lp[1]);
            }
            lp[0] = rp[0];
            lp[1] = rp[1];
            wait(&status);
        }
        
        if (strcmp(argv[0], "exit") == 0){
            exit(0);
        }
        
        for(int i = 0; i < 20; i++){
            argv[i] = 0;
        }
    }
}


