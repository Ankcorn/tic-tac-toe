#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

void print_board(char moves[3][3])
{
    cout << "   A     B     C \n";
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 0; j <= 18; j++)
        {
            if (j == 0 && (i + 1) % 3 == 0)
            {
                cout << (i + 1) / 3;
            }
            else if ((i + 1) % 3 == 0 && (j + 3) % 6 == 0)
            {
                int pos_i = (i + 1) / 3;
                int pos_j = (j + 3) / 6;
                cout << moves[pos_i - 1][pos_j - 1];
            }
            else if (j == 18)
            {
                cout << "\n";
            }
            else if (j != 0 && j % 6 == 0)
            {

                cout << "|";
            }
            else if (i % 3 == 0 && i != 9 && j != 0)
            {
                cout << "_";
            }
            else
            {
                cout << " ";
            }
        }
    }
}

bool check_move(int i, int j, char moves[3][3])
{
    if (i < 0 || i > 2 || j < 0 || j > 2)
    {
        cout << "POSITION OUT OF BOUNDS\n";
        return false;
    }

    if (moves[i - 1][j - 1] == '-')
    {
        cout << "THAT SPACE HAS ALREADY BEEN PLAYED\n";
        return false;
    }
    return true;
}

void clearConsole()
{
    // ANSI escape sequence to clear the console
    cout << "\033[2J\033[1;1H";
}
char check_win(char (&moves)[3])
{
    if (moves[0] == '0' && moves[1] == '0' && moves[2] == '0')
    {
        return '0';
    }

    if (moves[0] == 'x' && moves[1] == 'x' && moves[2] == 'x')
    {
        return 'x';
    }

    return 'd';
}
char check_result(char moves[3][3])
{
    char is_win = 'd';
    // check rows
    for (int i = 0; i < 3; i++)
    {
        is_win = check_win(moves[i]);
        if (is_win != 'd')
        {
            return is_win;
        }
    }

    // check cols
    for (int i = 0; i < 3; i++)
    {
        char positions[3] = {moves[0][i], moves[1][i], moves[2][i]};
        is_win = check_win(positions);
        if (is_win != 'd')
        {
            return is_win;
        }
    }

    // diag top to bottom
    char top_to_bottom[3] = {moves[0][0], moves[1][1], moves[2][2]};
    cout << "checking top to bottom";
    is_win = check_win(top_to_bottom);
    if (is_win != 'd')
    {
        return is_win;
    }
    // diag bottom to top
    char bottom_to_top[3] = {moves[2][0], moves[1][1], moves[0][2]};
    cout << "checking bottom to top";
    is_win = check_win(bottom_to_top);

    if (is_win != 'd')
    {
        return is_win;
    }
    return is_win;
}

int main()
{
    string start;
    char result;
    bool playing = true;
    char current = '0';
    char moves[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'},
    };

    cout << "Welcome to Awesome tic-tac-toe, press enter to start";
    getline(cin, start);
    clearConsole();
    while (playing)
    {

        string move;
        int i = -1;
        int j = -1;

        print_board(moves);
        while (i == -1 && j == -1)
        {
            cout << "It's " << current << " to move. Where would you like to go?\n";
            getline(cin, move);
            cout << "\n";

            if (move[0] == 49 || move[0] == 50 || move[0] == 51)
            {
                i = move[0] - 49;
                j = move[1] - 65;
            }
            else
            {
                i = move[1] - 49;
                j = move[0] - 65;
            }
            if (!check_move(i, j, moves))
            {
                i = -1;
                j = -1;
            }
        }

        moves[i][j] = current;

        result = check_result(moves);
        if (result != 'd')
        {
            playing = false;
        }
        else
        {
            if (current == '0')
            {
                current = 'x';
            }
            else
            {
                current = '0';
            }
        }

        clearConsole();
    }

    int victoryDance = 5;
    while (victoryDance != 0)
    {
        char winner[3][3] = {
            {current, current, current},
            {current, current, current},
            {current, current, current},
        };
        clearConsole();
        print_board(winner);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        clearConsole();
        char clear[3][3] = {
            {'-', '-', '-'},
            {'-', '-', '-'},
            {'-', '-', '-'},
        };
        print_board(clear);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        --victoryDance;
    }

    clearConsole();
    print_board(moves);
    cout << current << " Wins!\n";

    cout << "Thanks for playing\n";

    return 0;
}
