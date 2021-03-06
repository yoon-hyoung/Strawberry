#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
/*
 *
 *pt.Input data
 *
 */
char *texterase;
char *text;
char *email;
int IDsize = 0;
int textsize = 0;
int main()
{
    char *input; //save the sentence to show
    char *emailID;
    char c; //get character
    int inputsize = 0, pos = 0; //count input size
   	int emailsize = 5;
    int i;
    int pid = 0, exitstatus;
    int min, sec;
    //void myalarm(int signum); //sighandler
    
    signal(SIGALRM, myalarm);
    
    do {
        printf("Input \'a\' to save alarm >>");
        if( (c=getc(stdin)) == 'a') {
            pid = fork();
            if(pid != 0) {
                signal(SIGINT, SIG_IGN); //ignore sigint
                while(wait(&exitstatus) != pid);
                printf("alarm exited with status %d %d\n", exitstatus>>8, exitstatus&0377);
            }
        }
        else {
            printf("user input another spell\n");
            printf("Exit the alarm program\n");
            printf("users alarm will disappear\n");
            exit(1);
        }
        while(getchar() != '\n');
    } while(pid);
    
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
    pos = 6;
    printf("Input your email >>");
    while(( c=getc(stdin) )!= '\n') {
        if(pos+1 >= emailsize) {
            if(emailsize == 5) {
                emailID = malloc(BUF + (sizeof(char) * 6));
                strcpy(emailID, "mailx ");
            }
            else
                emailID = realloc(emailID, emailsize + BUF + sizeof(char) * 6);
            emailsize += BUF; //expands inputsize
        }
        emailID[pos++] = c;
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
}

