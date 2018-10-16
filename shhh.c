/*			Lab 2 			*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

main()
{
    char *path, *argv[20], buf[80], n, *p;

    int m, status, inword, continu;
    
    while(1) {

        inword = 0;
        p = buf;
        m = 0;
        continu=0;

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
             
        int p[2];
        pipe(p);
        
        if ( fork() == 0 ) {
            close(0);
            close(p[0]);
            close(p[1]);
            dup(p[0]);
            execvp( argv[0], argv );
            printf ( " didn't exec \n ");
        }
        else {
            close(1);
            close(p[0]);
            close(p[1]);
            dup(p[1]);
            execvp( argv[1], argv );
        }
        
        wait(&status);

    }
}

