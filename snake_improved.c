#include <stdio.h>
#include <curses.h> //recognice the pressed button, needs printw instead of printf
#include <stdlib.h>
#include <unistd.h> //for sleep

//compile with gcc -o snake snake.c -lncurses

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

//making fruits, gameover
void    setup()
{
    gameover = 0;
    x = height / 2;
    y = width / 2;
label1:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label1;
label2:
        fruity=rand() % 20;
        if (fruity == 0)
            goto label2;
    score = 0;
}

//drawing the boundary
void    draw()
{
    clear();    //from curses 
    for(i = 0; i < height; i++)
    {    
        for(j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0
            || j == width - 1)
                mvprintw(i, j, "#");
            else
            {
                if (i == x && j == y)
                    mvprintw(i, j, "S");
                else  if(i == fruitx && j == fruity)
                    mvprintw(i, j, "*");
                else
                    mvprintw(i, j, " ");
            }
        }
    }
    mvprintw(height, 0, "score = %d", score);
    mvprintw(height + 1, 0, "press x to quit the game");
    refresh();
}

//input for wasd
void input()
{
    nodelay(stdscr, TRUE);
    int ch = getch();
    if(ch != ERR)
    {
        switch(ch)
        {
            case 'a':
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'd':
                flag = 3;
                break;
            case 'w':
                flag = 4;
                break;
	       	case 'x':
                gameover = 1;
                break;
        }
    }
}

//movement for wasd
void move_snake()
{
    usleep(100000); // this makes lag for 0.1 sec = makes movement slower
    switch(flag)
    {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
		case 4:
            x--;
            break;
        default:
            break;
    }
    //score counting and making new fruit
    if (x < 0 || x >= height ||  y < 0 || y >= width)
        gameover = 1;
    if (x == fruitx && y == fruity)
    {
        while ((fruitx = rand() % 20) == 0);
        while ((fruity = rand() % 20) == 0);
        score += 5;
    }
}

int main()
{
    initscr();  //initalize curses mode
    int m, n;
    setup();
    while (!gameover)
    {
        draw();
        input();
        move_snake();
    }
    endwin(); //ends curses mode
    return (0);
}
