/* 

MADE BY: Bernardo Reis
VERSION: 4.1

*********************************
          INSTRUCTIONS
*********************************

    1 - Press W, A, S, D to move the cursor (#)
    2 - Press (1) to uncover the selected spot
    3 - Press (2) to put/remove a flag

*/

//LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//STRUCTURES
typedef struct cursor
{
    int x;
    int y;
} cursor_t;

//PROTOTYPES
int choose_size(int *n);
void create_cboard(int n, char board[][n]);
void create_pboard(int n, char board[][n]);
void print_board(int n, char board[][n], cursor_t cursor);
void receive_input(int n, char cboard[][n], char pboard[][n], int *go, cursor_t *cursor, int *score);
void uncover_board(int n, char cboard[][n], char pboard[][n], int x, int y, int *go, int *score);
void verify_victory(int n, char cboard[][n], int *go);
void clean_board(int n, char cboard[][n], char pboard[][n], int go);
void main_menu(int *m, int *n);
void instructions_menu(int *m);
void print_exit();
void print_gameover();
void print_victory();
void print_score(FILE *arq, int n, int score);
void set_highscore(FILE *arq, int score, int n);

//MAIN
int main()
{
    srand(time(NULL));

    FILE *arq = fopen("minesweeper_highscore.txt", "r+");

    while (1)
    {
        int m = 0;
        int n = 0;

        main_menu(&m, &n);

        if (m == 3)
        {
            print_exit();
            system("pause");
            fclose(arq);
            return 0;
        }

        if (n == 1)
            n = 9;

        if (n == 2)
            n = 16;

        if (n == 3)
            n = 22;

        char control_board[n][n];
        char play_board[n][n];

        create_cboard(n, control_board);
        create_pboard(n, play_board);

        int gameover = 0;
        int score = 0;

        cursor_t cursor = {0, 0};

        while (gameover != 1 && gameover != 2 && gameover != 3)
        {
            system("cls");
            printf("\n");
            print_score(arq, n, score);
            print_board(n, play_board, cursor);
            printf("\n");
            receive_input(n, control_board, play_board, &gameover, &cursor, &score);
            printf("\n");
            verify_victory(n, control_board, &gameover);
            system("cls");
            printf("\n");
            print_score(arq, n, score);
            print_board(n, play_board, cursor);
            printf("\n");
        }

        if (gameover == 1)
        {
            cursor.x = -1;
            cursor.y = -1;
            system("cls");
            printf("\n");
            clean_board(n, control_board, play_board, gameover);
            print_score(arq, n, score);
            print_board(n, play_board, cursor);
            print_gameover();
            system("pause");
        }

        else if (gameover == 2)
        {
            cursor.x = -1;
            cursor.y = -1;
            system("cls");
            printf("\n");
            clean_board(n, control_board, play_board, gameover);
            print_score(arq, n, score);
            print_board(n, play_board, cursor);
            print_victory();
            set_highscore(arq, score, n);
            system("pause");
        }

        else if (gameover == 3)
        {
            cursor.x = -1;
            cursor.y = -1;
            system("cls");
            printf("\n");
            clean_board(n, control_board, play_board, gameover);
            print_score(arq, n, score);
            print_board(n, play_board, cursor);
            print_exit();
            system("pause");
        }
    }

    system("pause");
    fclose(arq);
    return 0;
}

//FUNCTIONS
int choose_size(int *n)
{
    while (1)
    {
        system("cls");
        printf("\n");
        printf("     ***************************************\n");
        printf("              CHOOSE THE BOARD SIZE\n");
        printf("     ***************************************\n");
        printf("\n");
        printf("    Press the respective number to choose the option:\n");
        printf("\n");
        printf("    (1) 9x9\n");
        printf("    (2) 16x16\n");
        printf("    (3) 22x22\n");
        printf("\n");
        printf("    Press (4) to go back\n");

        while (1)
        {
            if (kbhit)
            {
                switch (getch())
                {
                case '1':
                    *n = 1;
                    return 1;

                case '2':
                    *n = 2;
                    return 1;

                case '3':
                    *n = 3;
                    return 1;

                case '4':
                    *n = 4;
                    return 0;

                default:
                    break;
                }
            }
        }
    }
}

void create_cboard(int n, char board[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 'o';

    if (n == 9)
    {
        int count = 0;
        int x, y;

        while (1)
        {
            x = rand() % n;
            y = rand() % n;

            if (board[x][y] != 'x')
            {
                board[x][y] = 'x';
                count++;
            }
            else
                continue;
            if (count == 10)
                break;
        }
    }

    if (n == 16)
    {
        int count = 0;
        int x, y;

        while (1)
        {
            x = rand() % n;
            y = rand() % n;

            if (board[x][y] != 'x')
            {
                board[x][y] = 'x';
                count++;
            }
            else
                continue;
            if (count == 40)
                break;
        }
    }

    if (n == 22)
    {
        int count = 0;
        int x, y;

        while (1)
        {
            x = rand() % n;
            y = rand() % n;

            if (board[x][y] != 'x')
            {
                board[x][y] = 'x';
                count++;
            }
            else
                continue;
            if (count == 99)
                break;
        }
    }
}

void create_pboard(int n, char board[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 'o';
}

void print_board(int n, char board[][n], cursor_t cursor)
{
    printf("     ");
    for (int i = 1; i <= 3 * n + 2; i++)
    {
        printf("-");
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
            {
                printf("    ");
                printf("|");
            }

            if (cursor.x == i && cursor.y == j)
                printf("%3c", '#');

            else
                printf("%3c", board[i][j]);

            if (j == n - 1)
                printf("%3c", '|');
        }
        printf("\n");
    }

    printf("     ");
    for (int i = 1; i <= 3 * n + 2; i++)
    {
        printf("-");
    }
    printf("\n");
}

void receive_input(int n, char cboard[][n], char pboard[][n], int *go, cursor_t *cursor, int *score)
{
    printf("    Press (4) to quit the current game");
    if (kbhit)
    {
        switch (getch())
        {
        case 'w':
            if (cursor->x - 1 >= 0)
                cursor->x -= 1;
            return;

        case 'a':
            if (cursor->y - 1 >= 0)
                cursor->y -= 1;
            return;

        case 's':
            if (cursor->x + 1 < n)
                cursor->x += 1;
            return;

        case 'd':
            if (cursor->y + 1 < n)
                cursor->y += 1;
            return;

        case '1':
        {
            uncover_board(n, cboard, pboard, cursor->x, cursor->y, go, score);
            return;
        }

        case '2':
        {
            if (pboard[cursor->x][cursor->y] == 'o')
                pboard[cursor->x][cursor->y] = '!';

            else if (pboard[cursor->x][cursor->y] == '!')
                pboard[cursor->x][cursor->y] = 'o';

            return;
        }
        case '4':
        {
            *go = 3;
            return;
        }

        default:
            return;
        }
    }
}

void uncover_board(int n, char cboard[][n], char pboard[][n], int x, int y, int *go, int *score)
{
    if (cboard[x][y] == 'x')
    {
        pboard[x][y] = 'x';
        *go = 1;
        return;
    }

    else if (cboard[x][y] == 'c')
    {
        return;
    }

    else
    {
        *score += 10;
        int count = 0;
        int index = 0;
        int aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0, aux5 = 0, aux6 = 0, aux7 = 0, aux8 = 0;

        if (y - 1 >= 0)
        {
            aux1++;
            if (cboard[x][y - 1] != 'x')
            {
                count++;
            }
            if (cboard[x][y - 1] == 'x')
            {
                index++;
            }
        }
        if (x - 1 >= 0)
        {
            aux2++;
            if (cboard[x - 1][y] != 'x')
            {
                count++;
            }
            if (cboard[x - 1][y] == 'x')
            {
                index++;
            }
        }
        if (y + 1 < n)
        {
            aux3++;
            if (cboard[x][y + 1] != 'x')
            {
                count++;
            }
            if (cboard[x][y + 1] == 'x')
            {
                index++;
            }
        }
        if (x + 1 < n)
        {
            aux4++;
            if (cboard[x + 1][y] != 'x')
            {
                count++;
            }
            if (cboard[x + 1][y] == 'x')
            {
                index++;
            }
        }
        if (y - 1 >= 0 && x + 1 < n)
        {
            aux5++;
            if (cboard[x + 1][y - 1] != 'x')
            {
                count++;
            }
            if (cboard[x + 1][y - 1] == 'x')
            {
                index++;
            }
        }
        if (x - 1 >= 0 && y + 1 < n)
        {
            aux6++;
            if (cboard[x - 1][y + 1] != 'x')
            {
                count++;
            }
            if (cboard[x - 1][y + 1] == 'x')
            {
                index++;
            }
        }
        if (y - 1 >= 0 && x - 1 >= 0)
        {
            aux7++;
            if (cboard[x - 1][y - 1] != 'x')
            {
                count++;
            }
            if (cboard[x - 1][y - 1] == 'x')
            {
                index++;
            }
        }
        if (y + 1 < n && x + 1 < n)
        {
            aux8++;
            if (cboard[x + 1][y + 1] != 'x')
            {
                count++;
            }
            if (cboard[x + 1][y + 1] == 'x')
            {
                index++;
            }
        }

        int aux = aux1 + aux2 + aux3 + aux4 + aux5 + aux6 + aux7 + aux8;

        if (aux == count)
        {
            cboard[x][y] = 'c';
            pboard[x][y] = ' ';

            if (aux1 == 1)
                if (cboard[x][y - 1] != 'c')
                    uncover_board(n, cboard, pboard, x, y - 1, go, score);

            if (aux2 == 1)
                if (cboard[x - 1][y] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y, go, score);

            if (aux3 == 1)
                if (cboard[x][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x, y + 1, go, score);

            if (aux4 == 1)
                if (cboard[x + 1][y] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y, go, score);

            if (aux5 == 1)
                if (cboard[x + 1][y - 1] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y - 1, go, score);

            if (aux6 == 1)
                if (cboard[x - 1][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y + 1, go, score);

            if (aux7 == 1)
                if (cboard[x - 1][y - 1] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y - 1, go, score);

            if (aux8 == 1)
                if (cboard[x + 1][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y + 1, go, score);
        }

        else if (aux != count)
        {
            pboard[x][y] = 48 + index;
            cboard[x][y] = 'c';
        }
    }
}

void verify_victory(int n, char cboard[][n], int *go)
{
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cboard[i][j] == 'o')
            {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 1)
        *go = 2;
}

void clean_board(int n, char cboard[][n], char pboard[][n], int go)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (cboard[i][j] == 'x')
                pboard[i][j] = 'x';
            if ((cboard[i][j] == 'o' || cboard[i][j] == 'c') && go == 3)
                pboard[i][j] = ' ';
        }
}

void main_menu(int *m, int *n)
{
    while (1)
    {
        system("cls");
        printf("\n");
        printf("   v.4.1\n");
        printf("    * * * * * * * * * * * * * * * * * * * * *\n");
        printf("   *           ##  ## # ##  # ####           *\n");
        printf("   *           # ## # # # # # #              *\n");
        printf("   *           #    # # #  ## ###            *\n");
        printf("   *           #    # # #   # #              *\n");
        printf("   *           #    # # #   # ####           *\n");
        printf("   *                                         *\n");
        printf("   *  #### #    # #### ####  ###  ####  ###  *\n");
        printf("   * #     #    # #    #    #   # #    #   # *\n");
        printf("   *  ###  #    # ###  ###  ####  ###  #  #  *\n");
        printf("   *     # # ## # #    #    #     #    # #   *\n");
        printf("   * ####  ##  ## #### #### #     #### #   # *\n");
        printf("    * * * * * * * * * * * * * * * * * * * * *\n");
        printf("\n");
        printf("                    (1) PLAY\n");
        printf("                 (2) INSTRUCTIONS\n");
        printf("                  (3) EXIT GAME\n");

        if (kbhit)
        {
            switch (getch())
            {
            case '1':
                *m = choose_size(n);
                if (*m == 1)
                    return;
                else
                    break;

            case '2':
                instructions_menu(m);
                break;

            case '3':
                *m = 3;
                return;

            default:
                break;
            }
        }
    }
}

void instructions_menu(int *m)
{
    while (1)
    {
        system("cls");
        printf("\n");
        printf("     ***************************************\n");
        printf("                  INSTRUCTIONS\n");
        printf("     ***************************************\n");
        printf("\n");
        printf("    - Press W, A, S, D to move the cursor (#)\n");
        printf("    - Press (1) to uncover the selected spot\n");
        printf("    - Press (2) to put/remove a flag\n");
        printf("    - Have fun!\n");
        printf("\n");
        printf("    Press (4) to go back");
        printf("\n");

        if (kbhit)
        {
            switch (getch())
            {
            case '4':
                return;
            default:
                break;
            }
        }
    }
}

void print_exit()
{
    printf("\n");
    printf("     ***************************************\n");
    printf("                     EXITED!\n");
    printf("     ***************************************\n");
    printf("\n");
}

void print_gameover()
{
    printf("\n");
    printf("     ***************************************\n");
    printf("                   GAME OVER!\n");
    printf("     ***************************************\n");
    printf("\n");
}

void print_victory()
{
    printf("\n");
    printf("     ***************************************\n");
    printf("                    VICTORY!\n");
    printf("     ***************************************\n");
    printf("\n");
}

void print_score(FILE *arq, int n, int score)
{
    rewind(arq);

    if (n == 9)
    {
        int highscore1, highscore2, highscore3;
        fscanf(arq, "%d", &highscore1, &highscore2, &highscore3);
        printf("     SCORE: %d          HIGHSCORE: %d\n", score, highscore1);
    }

    if (n == 16)
    {
        int highscore1, highscore2, highscore3;
        fscanf(arq, "%d %d %d", &highscore1, &highscore2, &highscore3);
        printf("     SCORE: %d          HIGHSCORE: %d\n", score, highscore2);
    }

    if (n == 22)
    {
        int highscore1, highscore2, highscore3;
        fscanf(arq, "%d %d %d", &highscore1, &highscore2, &highscore3);
        printf("     SCORE: %d          HIGHSCORE: %d\n", score, highscore3);
    }
}

void set_highscore(FILE *arq, int score, int n)
{
    rewind(arq);

    int highscore1, highscore2, highscore3;
    fscanf(arq, "%d %d %d", &highscore1, &highscore2, &highscore3);

    if (n == 9)
    {
        if (score > highscore1)
        {
            rewind(arq);
            fprintf(arq, "%d %d %d", score, highscore2, highscore3);
        }
    }

    if (n == 16)
    {
        if (score > highscore2)
        {
            rewind(arq);
            fprintf(arq, "%d %d %d", highscore1, score, highscore3);
        }
    }

    if (n == 22)
    {
        if (score > highscore3)
        {
            rewind(arq);
            fprintf(arq, "%d %d %d", highscore1, highscore2, score);
        }
    }
}