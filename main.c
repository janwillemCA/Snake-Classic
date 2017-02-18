/**
 * Created By Jan Willem Casteleijn.
 * Maintained By Henri Van Den Munt & Jan Willem Casteleijn
 * Console game Snake.
 * Features: Fully written in C ANSI 99 without Graphic Library's, Collision Detection.
 *
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void hidecursor();
void draw_food();
void draw_end();

int x = 9;
int prev_x;
int prev_y;
int y = 9;
int rand_x = 5;
int rand_y = 5;
int score = 0;
int snake_len = 0;
char food = 'f';

typedef struct node
{
    int val;
    struct node * next;
} node_t;


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


void push(node_t * head, int val)
{
    node_t * current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void print_list(node_t * head)
{
    node_t * current = head;

    while (current != NULL)
    {
        printf("Snake length: %d\n", current->val);
        current = current->next;
    }
}

void get_input(node_t * head)
{
    char c;

    while(y > LEFT_BORDER && y < RIGHT_BORDER && x > UPPER_BORDER && x < BOTTOM_BORDER)
    {
        if(kbhit())
        {
            c = getch();
        }

        print_list(head);

        draw_food(head, snake_len);

        switch(c)
        {
        case 'a':
            y--;
            draw_snake();
            field[x][y+1] = 's';
            system("cls");
            draw_field(field);
            field[x][y-1] = 's';

            break;
        case 'd':
            y++;
            field[x][y-1] = 's';
            draw_snake();
            system("cls");
            draw_field(field);
            field[x][y+1] = 's';

            break;
        case 's':
            x++;
            draw_snake();
            field[x-1][y] = 's';
            system("cls");
            draw_field(field);
            field[x+1][y] = 's';

            break;
        case 'w':
            x--;
            draw_snake();
            field[x+1][y] = 's';
            system("cls");
            draw_field(field);
            field[x-1][y] = 's';

            break;
        default:
            return;
        }
    }
}

void draw_menu(){
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
    while(nokeypressed){
        if(kbhit()){
            nokeypressed = false;
        }
    }
}

void generate_field(int height, int width){
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
    char tail = 't';

    field[x][y] = head;
    Sleep(GAME_SPEED);
}


void draw_food(node_t * head, int snake_len)
{
    srand(time(NULL));

    field[rand_x][rand_y] = food;

    if(x == rand_x && y == rand_y)
    {
        score++;
        snake_len = score;

        push(head, snake_len);

        rand_x = ( rand() % 15 ) + 2;
        rand_y = ( rand() % 15  ) + 2;
    }
}

void draw_end()
{
    system("cls");
    printf("%s", "GAME OVER");
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void menu()
{

}

int main()
{

    node_t * head = NULL;
    head = malloc(sizeof(node_t));
    if (head == NULL)
    {
        return 1;
    }

    head->val = 1;
    head->next = NULL;

    system("cls");

    hidecursor();

    draw_menu();

    system("cls");

    while(1)
    {
        system("cls");

        draw_field(field);

        get_input(head);

        Sleep(GAME_SPEED);
    }
    return 0;
}
