#pragma once
#include <vector>
#include <iostream>
#include <string>

enum class Player { EMPTY = 0, X = 1, O = 2 };

class TicTacToe {
private:
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    
public:
    TicTacToe();
    void reset();
    bool makeMove(int row, int col, Player player);
    bool isValidMove(int row, int col) const;
    Player checkWinner() const;
    bool isDraw() const;
    bool isGameOver() const;
    void displayBoard() const;
    std::vector<std::pair<int, int>> getAvailableMoves() const;
    std::vector<std::vector<Player>> getBoard() const { return board; }
    Player getCurrentPlayer() const { return currentPlayer; }
    void setCurrentPlayer(Player player) { currentPlayer = player; }
    
    // Convert board state to unique integer for Q-table indexing
    int getBoardStateHash() const;
    void setBoardFromHash(int hash);
    
    // Get reward for current state
    double getReward(Player player) const;
};
