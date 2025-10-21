#include "TicTacToe.h"
#include <iomanip>
#include <cmath>

TicTacToe::TicTacToe() : board(3, std::vector<Player>(3, Player::EMPTY)), currentPlayer(Player::X) {}

void TicTacToe::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = Player::EMPTY;
        }
    }
    currentPlayer = Player::X;
}

bool TicTacToe::makeMove(int row, int col, Player player) {
    if (isValidMove(row, col)) {
        board[row][col] = player;
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        return true;
    }
    return false;
}

bool TicTacToe::isValidMove(int row, int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == Player::EMPTY;
}

Player TicTacToe::checkWinner() const {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != Player::EMPTY && 
            board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != Player::EMPTY && 
            board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }
    
    // Check diagonals
    if (board[0][0] != Player::EMPTY && 
        board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    
    if (board[0][2] != Player::EMPTY && 
        board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    
    return Player::EMPTY;
}

bool TicTacToe::isDraw() const {
    if (checkWinner() != Player::EMPTY) return false;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Player::EMPTY) return false;
        }
    }
    return true;
}

bool TicTacToe::isGameOver() const {
    return checkWinner() != Player::EMPTY || isDraw();
}

void TicTacToe::displayBoard() const {
    std::cout << "\n  0   1   2\n";
    for (int i = 0; i < 3; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 3; j++) {
            char symbol = ' ';
            if (board[i][j] == Player::X) symbol = 'X';
            else if (board[i][j] == Player::O) symbol = 'O';
            
            std::cout << symbol;
            if (j < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  ---------\n";
    }
    std::cout << "\n";
}

std::vector<std::pair<int, int>> TicTacToe::getAvailableMoves() const {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Player::EMPTY) {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

int TicTacToe::getBoardStateHash() const {
    int hash = 0;
    int multiplier = 1;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            hash += static_cast<int>(board[i][j]) * multiplier;
            multiplier *= 3;
        }
    }
    return hash;
}

void TicTacToe::setBoardFromHash(int hash) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = static_cast<Player>(hash % 3);
            hash /= 3;
        }
    }
}

double TicTacToe::getReward(Player player) const {
    Player winner = checkWinner();
    if (winner == player) return 1.0;      // Win
    else if (winner != Player::EMPTY) return -1.0;  // Loss
    else if (isDraw()) return 0.5;         // Draw
    else return 0.0;                       // Game not over
}
