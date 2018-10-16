/*			Lab 2 			*/

#include <stdio.h>
#include <string.h>
#include <signal.h>

main()
{
    char *path, *argv[20], buf[80], n, *p;

    int m, status, inword, continu;

    int fd;
    int n1, n2, n3;
    
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
        
        if ((fd = open("input.txt", O_RDONLY)) == -1){
            perror("open failed");
        }
        
        read(fd, buf, 80);
        
        if ( n2 = fork() == 0 ) {
            read(fd, buf, 80);
            if ((n = creat("output.txt", 0750)) < 0)
                exit(-1);
            close(1);
            dup(n1);
            close(n1);
            execvp( argv[0], argv );
            exit(-1);
            printf ( " didn't exec \n ");
        }

        n3 = wait(&status);

    }
}

