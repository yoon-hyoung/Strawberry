#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#define BUF 10
#define SPACE 4
#define ROW 10

void set_up();

typedef struct printval{
	int dir;
	int col;
}printval;
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
	void myalarm(int signum); //sighandler
	
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

void close_child(int signum) {
	endwin();
	exit(signum);
}

void set_up()
{
	initscr();
	clear();
	signal(SIGINT, close_child);
}

void myalarm(int signum)
{
	int i;
	int pid = 0;
	pthread_t t1, t2;
	printval value;
	void *ring();
	void *printText(void *);
	FILE *fp;

	/*initialize value*/
	value.dir = +1;
	value.col = 0;

	fp = popen(email, "w");
	fprintf(fp,"Aram ringing now!");		
	pclose(fp);

	set_up();

    /*create pthread*/
    pthread_create(&t1, NULL, ring, NULL);
    pthread_create(&t2, NULL, (void *)printText,(void *) &value);
    
    /*start thread*/
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	
}

void *ring()
{
    while(1) {
        putchar('\a');
        putchar('\a');
        sleep(2);
    }
    return NULL;
}

void *printText(void *v)
{
    printval val = *(printval *)v;
    
    while(1) {
        move(ROW, val.col);
        addstr(text);
        refresh();
        sleep(2);
        move(ROW, val.col);
        addstr(texterase);
        refresh();
        sleep(2);
        /*chage dir when col reaches bound*/
        if(val.col+(BUF*(val.dir))+textsize > COLS-1)
            val.dir = -1;
        else if(val.col+(BUF*(val.dir)) < 0)
            val.dir = +1;
    
        val.col += (BUF*(val.dir));
    }
    
    return NULL;
}

