/**
 * Created By Jan Willem Casteleijn.
 * Maintained By Henri Van De Munt & Jan Willem Casteleijn
 * Console game Snake.
 * Features: Fully written in C ANSI 99 without Graphic Library's, Collision Detection.
 *
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include<time.h>

#include <sys/select.h>

#ifdef __unix__

//@TODO ad support for unix

#define OS_Windows 0
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <windows.h>

#endif

#define FIELD_WIDTH             20
#define FIELD_HEIGHT            20
#define GAME_SPEED              100
#define LEFT_BORDER             0
#define RIGHT_BORDER            19
#define BOTTOM_BORDER           19
#define UPPER_BORDER            0

void get_input();
void draw_field(char field[FIELD_WIDTH][FIELD_HEIGHT]);
void draw_snake();
void draw_food();
void draw_end();
void draw_menu();


int x = 9;
int y = 9;
int rand_x = 5;
int rand_y = 5;
int score = 0;
char food = 'f';

char field[FIELD_WIDTH][FIELD_HEIGHT] =
{
    {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 's', 'b'},
    {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
    {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}
};



void get_input()
{
    char c;

    while(y > LEFT_BORDER && y < RIGHT_BORDER && x > UPPER_BORDER && x < BOTTOM_BORDER)
    {
        if(kbhit())
        {
            c = getch();
        }
        draw_food();

        switch(c)
        {
        case 'a':
            y--;
            draw_snake();
            field[x][y+score+1] = 's';
            clear();
            draw_field(field);

            break;
        case 'd':
            y++;
            field[x][y-score-1] = 's';
            draw_snake();
            clear();
            draw_field(field);

            break;
        case 's':
            x++;
            draw_snake();
            field[x-score-1][y] = 's';
            clear();
            draw_field(field);

            break;
        case 'w':
            x--;
            draw_snake();
            field[x+score+1][y] = 's';
            clear();
            draw_field(field);

            break;
        default:
            return;
        }
    }
}


int kbhit(void)
{
  struct timeval tv;
  fd_set read_fd;

  /* Do not wait at all, not even a microsecond */
  tv.tv_sec=0;
  tv.tv_usec=0;

  /* Must be done first to initialize read_fd */
  FD_ZERO(&read_fd);

  /* Makes select() ask if input is ready:
   * 0 is the file descriptor for stdin    */
  FD_SET(0,&read_fd);

  /* The first parameter is the number of the
   * largest file descriptor to check + 1. */
  if(select(1, &read_fd,NULL, /*No writes*/NULL, /*No exceptions*/&tv) == -1)
    return 0;  /* An error occured */

  /*  read_fd now holds a bit map of files that are
   * readable. We test the entry for the standard
   * input (file 0). */
  
if(FD_ISSET(0,&read_fd))
    /* Character pending on stdin */
    return 1;

  /* no characters were pending */
  return 0;
}

void draw_menu()
{
    int i;
    printf("********************\n");
    for (i = 0; i < 5; ++i)
    {
        printf("*                  *\n");
    }
    printf("*    S n a k e     *\n");
    printf("*                  *\n");
    printf("*    Press any     *\n");
    printf("*   key to start   *\n");
    for (i = 0; i < 11; ++i)
    {
        printf("*                  *\n");
    }
    printf("********************\n");
    bool nokeypressed = true;
    while(nokeypressed)
    {
        if(kbhit())
        {
            nokeypressed = false;
        }
    }
}

void generate_field(int height, int width)
{
    //@TODO
}

void draw_field(char field[20][20])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            switch (field[i][j])
            {
            case 'b':
                printf("*");
                break;
            case 's':
                printf(" ");
                break;
            case 'h':
                printf("*");
                break;
            case 'f':
                printf("#");
                break;
            case 't':
                printf("*");
                break;
            }
        }
        printf("\n");
    }

    printf("\n Score: %d\n", score);
}

void draw_snake()
{
    char head = 'h';
    field[x][y] = head;
    sleep(GAME_SPEED);
}


void draw_food()
{
    srand(time(NULL));

    field[rand_x][rand_y] = food;

    if(x == rand_x && y == rand_y)
    {
        score++;

        rand_x = ( rand() % 15 ) + 2;
        rand_y = ( rand() % 15  ) + 2;
    }
}

void draw_end()
{
            clear();
    printf("%s", "GAME OVER");
}


int main()
{

    draw_menu();

    while(1)
    {
        clear();

        draw_field(field);

        get_input();

        sleep(GAME_SPEED);
    }
    return 0;
}
