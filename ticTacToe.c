#include <stdio.h>

char board[3][3];

void initializeBoard();
void displayBoard();
int playerMove(char player);
char checkWinner();
int isDraw();
void playGame(char player1Symbol, char player2Symbol);
void choosePlayerSymbols(char* player1Symbol, char* player2Symbol);

int main() {
    char playAgain;
    char player1Symbol, player2Symbol;

    printf("\n==============================\n");
    printf("    !    WELCOME TO    !    \n");
    printf("      TIC TAC TOE GAME      \n");
    printf("==============================\n");
    printf("You can choose your symbols before each game!\n");

    do {
        choosePlayerSymbols(&player1Symbol, &player2Symbol);
        printf("Player 1: %c     Player 2: %c\n", player1Symbol, player2Symbol);
        playGame(player1Symbol, player2Symbol);

        printf("\n->Would you like to play again? (y/n): ");
        scanf_s(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\n->Thanks for playing! Goodbye!\n");
    return 0;
}

void initializeBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = num++;
}

void displayBoard() {
    printf("\nCurrent Board:\n\n");
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n-------------\n");
    }
    printf("\n");
}

int playerMove(char player) {
    int move;
    printf("Player %c, choose a cell (1-9): ", player);
    scanf_s("%d", &move);

    if (move < 1 || move > 9) {
        printf("-> Invalid input! Please enter a number from 1 to 9.\n");
        return 0;
    }

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O') {
        printf("-> Cell already taken! Choose another one.\n");
        return 0;
    }

    board[row][col] = player;
    return 1;
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    return ' ';
}

int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

void playGame(char player1Symbol, char player2Symbol) {
    initializeBoard();
    char currentPlayer = player1Symbol;
    char winner = ' ';
    int valid;

    while (1) {
        displayBoard();
        do {
            valid = playerMove(currentPlayer);
        } while (!valid);

        winner = checkWinner();
        if (winner == player1Symbol || winner == player2Symbol) {
            displayBoard();
            printf("-> Player %c wins the game! Congratulations!\n", winner);
            break;
        }

        if (isDraw()) {
            displayBoard();
            printf("-> It's a draw! Well played both players!\n");
            break;
        }

        currentPlayer = (currentPlayer == player1Symbol) ? player2Symbol : player1Symbol;
    }
}

void choosePlayerSymbols(char* player1Symbol, char* player2Symbol) {
    char choice;
    printf("\n-> Player 1, choose your symbol (X or O): ");
    while (1) {
        scanf_s(" %c", &choice);
        if (choice == 'X' || choice == 'x') {
            *player1Symbol = 'X';
            *player2Symbol = 'O';
            break;
        }
        else if (choice == 'O' || choice == 'o') {
            *player1Symbol = 'O';
            *player2Symbol = 'X';
            break;
        }
        else {
            printf("-> Invalid input. Please enter 'X' or 'O': ");
        }
    }
}
