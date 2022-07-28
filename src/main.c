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

const char operation_symbols[4]={'+','-','*','/'};

typedef struct _tile{
    int x, y, h, w;
    
}TILE;

void init_tile(TILE *tile);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void print_help();
short select_operation(short *operation,short *num1, short *num2);

int main(int argc, char **argv){
    
    short input_ans = 0, operation = 0;
    short num1 = 0, num2 = 0, result = 0;
    char ch; 
    static short score = 0;
    time_t t;
    TILE tile;

    WINDOW *question_w;
    WINDOW *answer_w;

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
    
    
    initscr();
    cbreak();
    //noecho();
    keypad(stdscr, TRUE);

    refresh();
    init_tile(&tile);
    question_w = create_newwin(tile.h, tile.w, tile.y-3, tile.x);
    answer_w= create_newwin(tile.h, tile.w, tile.y+3, tile.x);
    mvprintw(10,10,"Score: %d", score);
    refresh();

    wmove(answer_w, HEIGHT/2, WIDTH/2);
    wrefresh(answer_w);

    while((ch = getch()) != 'q'){
        num1 = rand() % atoi(argv[1]);
        num2 = rand() % atoi(argv[1]);
        operation = rand() % 4;
        result = select_operation(&operation, &num1, &num2);
        //printf(" Score: %hd \n %hd %c %hd = ", score,num1, operation_symbols[operation], num2);
        //scanf("%hd", &input_ans);
        mvwprintw(question_w,HEIGHT/2,(WIDTH-strlen("x -- x"))/2,"%d %c %d", num1,operation_symbols[operation], num2);
        wrefresh(question_w);
        mvwscanw(answer_w, HEIGHT/2, WIDTH/2, "%hd", &input_ans);
        wrefresh(answer_w);
        //printw("\n %hn %c %hn ",&num1, operation_symbols[operation],&num2);
        //printw("\n %d -- %d ",input_ans, select_operation(&operation, &num1, &num2));
        mvprintw(10,10,"Score: %d", score);
        if(result == input_ans){
            score+=1; //update score
            refresh();
        }
    }
    endwin();

    
    //for(short i=0; i<9; i++){
    //    num1 = rand() % atoi(argv[1]);
    //    num2 = rand() % atoi(argv[1]);
    //    operation = rand() % 4;
    //    select_operation(&operation, &num1, &num2);
    //    printf(" Score: %hd \n %hd %c %hd = ", score,num1, operation_symbols[operation], num2);
    //    scanf("%hd", &input_ans);
    //    if(select_operation(&operation, &num1, &num2) == input_ans){
    //        score+=1; //update score
    //    }
    //}
    

    return 0;
}

void print_help(){

    printf("\t Just one argument is enough\n");
    printf("\t Select Range upto 10,000\n");

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

short select_operation(short *operation, short *num1, short *num2){
    short result;

    if(*(operation) == 0){
        result=*(num1)+*(num2);
    }
    if(*(operation) == 1){
        result=*(num1) - *(num2);
    }
    if(*(operation) == 2){
        result=*(num1) * *(num2);
    }
    else if(*(operation) == 3){
        result=*(num1) / *(num2);
    }

    //printf("result: %d \n", result);
    return result;
}

