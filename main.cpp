#include <iostream>
#include <unistd.h>
using namespace std;

// variables

int arr[6][7] = {           // 1 - X, 2 - O (downward - column, sideward - row)
    {0, 0, 0, 0, 0, 0, 0},  // 0
    {0, 0, 0, 0, 0, 0, 0},  // 1
    {0, 0, 0, 0, 0, 0, 0},  // 2
    {0, 0, 0, 0, 0, 0, 0},  // 3
    {0, 0, 0, 0, 0, 0, 0},  // 4
    {0, 0, 0, 0, 0, 0, 0}}; // 5

char turn = 'X';
int winner = 0;

void board();
int insert(int n);
int checkWin();
char switchTurn();
void greet();
int convertTurn();
void exit();

int main()
{
    int num;

    // game loop

    do
    {
        board();

        cout << "Enter column to insert " << turn << " :- ";
        try
        {
            cin >> num;
            if (num > 7 or num < 1)
            {
                throw(num);
            }
            int got = insert(num);
            if (got)
            {
                throw(2);
            }
        }
        catch (int n)
        {
            if (n == 2)
            {
                cout << "** Invalid Choice - Column is already full **\n";
                sleep(1.5);
            }
            else
            {
                cin.clear();
                cin.ignore();
                cout << "************ Invalid Choice ************\n";
                sleep(1);
                continue;
            }
        }

        winner = checkWin();
        if (winner)
        {
            break;
        }

        turn = switchTurn();
    } while (1);

    greet();

    return 0;
}

void exit()
{
    cout << "Bye :)";
    sleep(2);
}

char switchTurn()
{
    switch (turn)
    {
    case 'X':
        return 'O';
        break;

    case 'O':
        return 'X';
        break;

    default:
        break;
    }
    return ' ';
}

void greet()
{
    system("cls");
    board();

    switch (winner)
    {
    case 1:
        cout << "\nPlayer X Won !\n";
        break;

    case 2:
        cout << "\nPlayer O Won !\n";
        break;

    case 3:
        cout << "\n\nMatch Was Draw !\n";
        break;

    default:
        break;
    }

    // Re - play

    char re;

    cout << "\nDo you want to play again (y/n) :- ";
    cin >> re;

    switch (re)
    {
    case 'y':
        for (int col = 0; col < 6; col++)
        {
            for (int row = 0; row < 7; row++)
            {
                arr[col][row] = 0;
            }
        }
        turn = 'X';
        winner = 0;
        main();
        break;

    case 'n':
        exit();
        break;

    default:
        break;
    }
}

int convertTurn()
{
    switch (turn)
    {
    case 'X':
        return 1;
        break;

    case 'O':
        return 2;
        break;

    default:
        break;
    }
    return 0;
}

void board()
{
    // system("cls");

    cout << "--------- 4 in row ( By Viraj Mewal ) ---------" << endl
         << endl;
    for (int col = 0; col < 6; col++)
    {
        if (col == 0)
        {
            for (int i = 0; i < 7; i++)
            {
                if (i == 10)
                {
                    cout << " ___ ";
                }
                else
                {
                    cout << " ___";
                }
            }
            cout << endl;
        }
        for (int row = 0; row < 7; row++)
        {
            switch (arr[col][row])
            {
            case 0:
                if (row == 0)
                {
                    cout << "|   |";
                }
                else
                {
                    cout << "   |";
                }
                break;

            case 1:
                if (row == 0)
                {
                    cout << "| X |";
                }
                else
                {
                    cout << " X |";
                }
                break;

            case 2:
                if (row == 0)
                {
                    cout << "| O |";
                }
                else
                {
                    cout << " O |";
                }
                break;

            default:
                break;
            }
        }

        cout << endl;
        for (int i = 0; i < 7; i++)
        {
            if (i == 10)
            {
                cout << " ___ ";
            }
            else
            {
                cout << " ___";
            }
        }
        cout << endl;
    }
    for (int i = 1; i <= 7; i++)
    {
        cout << "  " << i << " ";
    }
    cout << endl
         << endl;
}

int checkWin()
{
    for (int col = 0; col < 6; col++)
    {
        for (int row = 0; row < 7; row++)
        {
            bool checkDiagonallyLeft = false, checkDiagonallyRight = false;
            if (row > 2 and col < 3)
            {
                checkDiagonallyLeft = true;
            }
            if (row < 4 and col < 3)
            {
                checkDiagonallyRight = true;
            }
            // vertical
            if (arr[col][row] != 0 and
                arr[col][row] == arr[col][row + 1] and
                arr[col][row] == arr[col][row + 2] and
                arr[col][row] == arr[col][row + 3])
            {
                return arr[col][row];
            }

            // horizontal
            else if (arr[col][row] != 0 and
                     arr[col][row] == arr[col + 1][row] and
                     arr[col][row] == arr[col + 2][row] and
                     arr[col][row] == arr[col + 3][row])
            {
                return arr[col][row];
            }

            // diagonally right
            else if (arr[col][row] != 0 and
                     arr[col][row] == arr[col + 1][row + 1] and
                     arr[col][row] == arr[col + 2][row + 2] and
                     arr[col][row] == arr[col + 3][row + 3] and
                     checkDiagonallyRight)
            {
                return arr[col][row];
            }

            // diagonally left
            else if (arr[col][row] != 0 and
                     arr[col][row] == arr[col + 1][row - 1] and
                     arr[col][row] == arr[col + 2][row - 2] and
                     arr[col][row] == arr[col + 3][row - 3] and
                     checkDiagonallyLeft)
            {

                return arr[col][row];
            }
        }
    }

    bool draw = false, breakthis = false;

    for (int col = 0; col < 6; col++)
    {
        for (int row = 0; row < 7; row++)
        {
            if (arr[col][row] == 0)
            {
                draw = false;
                breakthis = true;
                break;
            }
            else
            {
                draw = true;
            }
        }

        if (breakthis)
        {
            break;
        }
    }

    if (draw)
    {
        return 3;
    }

    return 0;
}

int insert(int num)
{
    for (int col = 5; col >= 0; col--)
    {
        if (!arr[col][num - 1])
        {
            // cout << "Value is :- " << col << endl;
            arr[col][num - 1] = convertTurn();
            break;
        }
        else if (col == 0 and arr[col][num - 1])
        {
            return 1;
        }
    }
    return 0;
}