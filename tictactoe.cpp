#include <iostream>
using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';
struct Move {
    int row, col;
};

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}
int evaluate(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }
    return 0;
}
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMovesLeft(board)) return 0;
    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}
Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
bool checkWin(char board[3][3], char player) {
    return (evaluate(board) == (player == AI ? 10 : -10));
}
int main() {
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };
    cout << "Tic-Tac-Toe: AI (O) vs Human (X)\n";
    printBoard(board);
    bool humanTurn = true;
    while (true) {
        if (humanTurn) {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (board[row][col] != EMPTY) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[row][col] = HUMAN;
            if (checkWin(board, HUMAN)) {
                printBoard(board);
                cout << "Human wins!\n";
                break;
            }
            humanTurn = false;
        } else {
            Move bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = AI;
            if (checkWin(board, AI)) {
                printBoard(board);
                cout << "AI wins!\n";
                break;
            }
            humanTurn = true;
        }
        printBoard(board);
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
