/* 

MADE BY: Bernardo Reis
VERSION: 1.1

*********************************
          INSTRUCTIONS
*********************************

1 - Type the respective number to select each option\n
2 - Type the coordinates in the following format: (line) (column)
3 - Have fun! 

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int choose_size(int *n);
void create_board(int n, char board[][n]);
void print_board(int n, char board[][n]);
void receive_input(int n, char cboard[][n], char pboard[][n], int *go);
void uncover_board(int n, char cboard[][n], char pboard[][n], int x, int y, int *go);
void verify_victory(int n, char cboard[][n], int *go);
void clean_board(int n, char cboard[][n], char pboard[][n], int go);

int main()
{
    srand(time(NULL));

    printf("\n");
    printf("   v.1.1\n");
    printf("   ***************************************\n");
    printf("   ##  ## # ##  # ####            \n");
    printf("   # ## # # # # # #               \n");
    printf("   #    # # #  ## ###             \n");
    printf("   #    # # #   # #               \n");
    printf("   #    # # #   # ####            \n");
    printf("\n");
    printf("    #### #    # #### ####  ###  ####  ###   \n");
    printf("   #     #    # #    #    #   # #    #   #  \n");
    printf("    ###  #    # ###  ###  ####  ###  #  #   \n");
    printf("       # # ## # #    #    #     #    # #    \n");
    printf("   ####  ##  ## #### #### #     #### #   #  \n");
    printf("   ***************************************\n");
    printf("\n");

    printf("\n");
    printf("   ***************************************\n");
    printf("                INSTRUCTIONS\n");
    printf("   ***************************************\n");
    printf("\n");
    printf("   1 - Type the respective number to select each option\n");
    printf("   2 - Type the coordinates in the following format: (line) (column)\n");
    printf("   3 - Have fun!");
    printf("\n");

    int n;
    choose_size(&n);

    if (n == 1)
        n = 9;

    if (n == 2)
        n = 16;

    if (n == 3)
        n = 22;

    if(n == 4)
    {
        printf("\n");
        printf("   ***************************************\n");
        printf("                   EXITED!\n");
        printf("   ***************************************\n");
        system("pause");
        return 0;
    }

    char control_board[n][n];

    create_board(n, control_board);

    char play_board[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            play_board[i][j] = 'o';

    int gameover = 0;

    while (gameover != 1 && gameover != 2 && gameover != 3)
    {
        system("cls");
        printf("\n");
        print_board(n, play_board);
        printf("\n");
        receive_input(n, control_board, play_board, &gameover);
        printf("\n");
        verify_victory(n, control_board, &gameover);
        system("cls");
        print_board(n, play_board);
        printf("\n");
    }

    if (gameover == 1)
    {
        system("cls");
        printf("\n");
        clean_board(n, control_board, play_board, gameover);
        print_board(n, play_board);
        printf("\n");
        printf("   ***************************************\n");
        printf("                 GAME OVER!\n");
        printf("   ***************************************\n");
    }

    else if (gameover == 2)
    {
        system("cls");
        printf("\n");
        clean_board(n, control_board, play_board, gameover);
        print_board(n, play_board);
        printf("\n");
        printf("   ***************************************\n");
        printf("                  VICTORY!\n");
        printf("   ***************************************\n");
    }

    else if (gameover == 3)
    {
        system("cls");
        printf("\n");
        clean_board(n, control_board, play_board, gameover);
        print_board(n, play_board);
        printf("\n");
        printf("   ***************************************\n");
        printf("                   EXITED!\n");
        printf("   ***************************************\n");
    }

    system("pause");
    return 0;
}

int choose_size(int *n)
{
    printf("\n");
    printf("   Choose the board size:\n");
    printf("   (1) 9x9\n");
    printf("   (2) 16x16\n");
    printf("   (3) 22x22\n");
    printf("   (4) Exit game\n");

    while (1)
    {
        printf("   ");
        scanf("%d", n);
        printf("\n");

        if (*n == 1 || *n == 2 || *n == 3 || *n == 4)
            break;
        else
        {
            printf("   Invalid entry!\n");
            printf("\n");
        }
    }
}

void create_board(int n, char board[][n])
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

void print_board(int n, char board[][n])
{
    printf("    ");
    for (int i = 1; i <= n; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
                printf("%3d ", i + 1);
            printf("%3c", board[i][j]);

            if (j == n - 1)
                printf(" %3d", i + 1);
        }
        printf("\n");
    }
    printf("\n");

    printf("    ");
    for (int i = 1; i <= n; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
}

void receive_input(int n, char cboard[][n], char pboard[][n], int *go)
{
    int z;
    printf("   Choose an action:\n");
    printf("   (1) Discover location\n");
    printf("   (2) Put/remove flag\n");
    printf("   (3) Exit the game\n");

    while (1)
    {
        printf("   ");
        scanf("%d", &z);
        printf("\n");
        if (z == 1 || z == 2 || z == 3)
            break;
        else
        {
            printf("   Invalid entry!\n");
            printf("\n");
        }
    }

    if (z == 1)
    {
        int x, y;
        while (1)
        {
            printf("   Type (-1) to go back\n");
            printf("   Type the coordinates: ");
            scanf("%d", &x);

            if (x != -1)
            {
                scanf("%d", &y);
                if (y != -1)
                {
                    if (x > n || y > n || x < 0 || y < 0)
                    {
                        printf("\n");
                        printf("   Invalid coordinates. Type again!\n");
                        printf("\n");
                    }
                    else
                    {
                        x -= 1;
                        y -= 1;
                        break;
                    }
                }
                else
                    break;
            }
            else
                break;
        }
        if (x != -1 && y != -1)
            uncover_board(n, cboard, pboard, x, y, go);
    }

    if (z == 2)
    {
        int x, y;
        while (1)
        {
            printf("   Type (-1) to go back\n");
            printf("   Type the coordinates: ");
            scanf("%d", &x);

            if (x != -1)
            {
                scanf("%d", &y);
                if (y != -1)
                {
                    if (x > n || y > n || x < 0 || y < 0)
                    {
                        printf("\n");
                        printf("   Invalid coordinates. Type again!\n");
                        printf("\n");
                    }
                    else
                    {
                        x -= 1;
                        y -= 1;
                        break;
                    }
                }
                else
                    break;
            }
            else
                break;
        }
        if (x != -1 && y != -1)
        {
            if (pboard[x][y] != '!')
                pboard[x][y] = '!';
            else
                pboard[x][y] = 'o';
        }
    }

    if (z == 3)
        *go = 3;
}

void uncover_board(int n, char cboard[][n], char pboard[][n], int x, int y, int *go)
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
                    uncover_board(n, cboard, pboard, x, y - 1, go);

            if (aux2 == 1)
                if (cboard[x - 1][y] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y, go);

            if (aux3 == 1)
                if (cboard[x][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x, y + 1, go);

            if (aux4 == 1)
                if (cboard[x + 1][y] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y, go);

            if (aux5 == 1)
                if (cboard[x + 1][y - 1] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y - 1, go);

            if (aux6 == 1)
                if (cboard[x - 1][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y + 1, go);

            if (aux7 == 1)
                if (cboard[x - 1][y - 1] != 'c')
                    uncover_board(n, cboard, pboard, x - 1, y - 1, go);

            if (aux8 == 1)
                if (cboard[x + 1][y + 1] != 'c')
                    uncover_board(n, cboard, pboard, x + 1, y + 1, go);
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