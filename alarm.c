#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>

char *texterase;
char *text;
char *email;
int IDsize = 0;
int textsize = 0;
int main()
{
    char *input; //save the sentence to show
    char *emailID
    char c; //get character
    int inputsize = 0, pos = 0; //count input size
    int emailsize = 0;
    int i;
    int min, sec;
    //void myalarm(int signum); //sighandler
    
    //signal(SIGALRM, myalarm);
    
    printf("Input the text >>");
    
    while(( c=getc(stdin) )!= '\n') {
        if(pos+1 >= inputsize) {
            if(inputsize == 0)
                input = malloc(BUF);
            else
                input = realloc(input, inputsize + BUF);
            inputsize += BUF; //expands inputsize
        }
        input[pos++] = c;
    }
    textsize = pos;
    text = malloc(pos);
    strncpy(text, input, pos);
    texterase = malloc(pos);
    for(i = 0; i < pos; i++)
        texterase[i] = ' ';
    
    /*get email address*/
    pos = 0;
    printf("Input your email >>");
    while(( c=getc(stdin) )!= '\n') {
        if(pos+1 >= emailsize) {
            if(emailsize == 0)
                emailID = malloc(BUF);
            else
                emailID = realloc(input, inputsize + BUF);
            emailsize += BUF; //expands inputsize
        }
        input[pos++] = c;
    }
    IDsize = pos;
    email = malloc(pos);
    strncpy(email, emailID, pos);
    
    /*get time*/
    printf("Input time (minute second)>>");
    scanf("%d",&min); scanf("%d",&sec);
    
    sec += min * 60;
    alarm(sec);
    pause();
    endwin();
}

