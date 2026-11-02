#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 3

char board[SIZE][SIZE];

void init_board(void) {
    char c = '1';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = c++;
}

void print_board(void) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("     |     |     \n");
        printf("  %c  |  %c  |  %c  \n", board[i][0], board[i][1], board[i][2]);
        if (i < SIZE - 1)
            printf("_____|_____|_____\n");
        else
            printf("     |     |     \n");
    }
    printf("\n");
}
int make_move(int cell, char player) {
    if (cell < 1 || cell > 9)
        return 0;
    int row = (cell - 1) / SIZE;
    int col = (cell - 1) % SIZE;
    if (board[row][col] == 'X' || board[row][col] == 'O')
        return 0;
    board[row][col] = player;
    return 1;
}

/* Returns 1 if the given player has won */
int check_win(char p) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return 1; /* rows */
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) return 1; /* columns */
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return 1;     /* diagonal */
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return 1;     /* anti-diagonal */
    return 0;
}

int is_draw(void) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

/* Reads an integer safely; returns -1 on bad input */
int read_cell(void) {
    char line[32];
    if (fgets(line, sizeof line, stdin) == NULL)
        exit(0);
    char *end;
    long v = strtol(line, &end, 10);
    if (end == line)
        return -1;
    return (int)v;
}

int play_game(void) {
    char player = 'X';
    init_board();

    while (1) {
        print_board();
        printf("Player %c, choose a cell (1-9): ", player);
        int cell = read_cell();

        if (!make_move(cell, player)) {
            printf("Invalid move! Pick an empty cell between 1 and 9.\n");
            continue;
        }

        if (check_win(player)) {
            print_board();
            printf("*** Player %c wins! ***\n", player);
            return 0;
        }
        if (is_draw()) {
            print_board();
            printf("It's a draw!\n");
            return 0;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
}

int main(void) {
    printf("=== TIC TAC TOE ===\n");
    printf("Player 1 = X, Player 2 = O\n");

    char again;
    do {
        play_game();
        printf("\nPlay again? (y/n): ");
        char line[16];
        if (fgets(line, sizeof line, stdin) == NULL)
            break;
        again = tolower((unsigned char)line[0]);
    } while (again == 'y');

    printf("Thanks for playing!\n");
    return 0;
}