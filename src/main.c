#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define ERROR "\033[1;31m"
#define SUCCESS "\033[1;32m"
#define FAIL "\033[0;91m"
#define WHITE "\033[00m"

#define HEIGHT 5
#define WIDTH 15

enum _mode{
    add,
    sub,
    multi,
    divi
};

typedef struct _tile{
    int x, y, h, w;
    
}TILE;

void init_tile(TILE *tile);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void print_help();
short *update_score(short *score, short *input_ans, int *num1, int *num2);

int main(int argc, char **argv){
    
    short num1, num2; 

    char ch, input_ans;
    static short score = 0;
    time_t t;
    TILE tile;
    WINDOW *question;
    WINDOW *answer;

    if(argc < 2){
	printf("ERROR: %sNot enough arguments %s\n",ERROR,WHITE);
	print_help();
	exit(EXIT_FAILURE);
    }else if (argc > 2){
	printf("ERROR: %sToo many arguments %s\n",ERROR,WHITE);
	print_help();
	exit(EXIT_FAILURE);
    }
    srand((unsigned) time(&t));
    num1 = rand() % atoi(argv[1]);
    num2 = rand() % atoi(argv[1]);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();
    init_tile(&tile);
    question = create_newwin(tile.h, tile.w, tile.y-3, tile.x);
    answer= create_newwin(tile.h, tile.w, tile.y+3, tile.x);
    mvwprintw(question,HEIGHT/2,(WIDTH-strlen("x -- x"))/2,"%d -- %d", num1, num2);
    wrefresh(question);
    refresh();

    while((ch = getch()) != 'q'){


	switch(ch){
	    case 'e':
		mvwprintw(answer, HEIGHT/2,(WIDTH/4),"%s", input_ans);
		wrefresh(answer);
		break;
	}
    }
    endwin();
    
    /*
    int test1 = 0;
    int test2 = 3;
    while(num1 !=0){
	update_score(&score, &input_ans, &test1, &test2);
	printf("main: %d \n", score);
	num1--;
    }*/
    return 0;
}

void print_help(){

    printf("Just one argument is enough\n");
    printf("Select Range upto 10,000\n");

}

void init_tile(TILE *tile){

    tile->h=HEIGHT;
    tile->w=WIDTH;
    tile->y=(LINES - (tile->h))/2;
    tile->x=(COLS - (tile->w))/2;
}

WINDOW *create_newwin(int height, int width, int starty, int startx){

    WINDOW *local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return (local_win);
}

short *update_score(short *score, short *input_ans, int *num1, int *num2){
    int calc_answer = *(num1)+*(num2);
    printf("%d -- %d \n", *(num1), *(num2));
    if(calc_answer == *(input_ans)){
	*(score)+=1;
	printf("func: %d \n", *(score));
    }
    return score;
}
