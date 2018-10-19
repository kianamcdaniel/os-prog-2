# os-prog-2

hello again! 

please follow the steps below to run my **pre.c** program

1) ssh into zeus.cs.txstate.edu
2) cd into the directory that my program's .c files are located
3) enter the command: gcc -std=c99 pre.c -o pre
    - this compiles pre.c 

please follow the steps below to run my **sort.c** program 

1) ssh into zeus.cs.txstate.edu
2) cd into the directory that my program's .c files are located
3) enter the command: gcc -std=c99 sort.c -o sort
    - this compiles sort.c 

please follow the steps below to run my **shhh.c** program & check it's functionality! 

1) ssh into zeus.cs.txstate.edu
2) cd into the directory that my program's .c files are located
3) enter the command: gcc -std=gnu99 shhh.c -o shhh
    - this compiles shhh.c 
4) enter the command: ./shhh
    - this will run shhh.c 
5) 'shhh>' will be printed to the console, this is your prompt to enter a command 
6) enter the following commands to test the functionality of the program
      shhh> **ls**
      
      shhh> **ls -t -al**
      
      shhh> **cat input.txt**
      
      shhh> **ls -al > output.txt**
      
      shhh> **cat output.txt**
      
      shhh> **rm output.txt**
      
      shhh> **ls | ls -t**
      
      shhh> **ls | ls -t | ls -al**
      
      shhh> **./pre < input.txt | ./sort > output.txt**
      
      shhh> **cat output.txt**
