#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>

char *texterase;
char *text;
int textsize = 0;
int main()
{
    char *input; //save the sentence to show
    char c; //get character
    int inputsize = 0, pos = 0; //count input size
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
    
    /*get time*/
    printf("Input time (minute second)>>");
    scanf("%d",&min); scanf("%d",&sec);
    
    sec += min * 60;
    alarm(sec);
    pause();
    endwin();
}

