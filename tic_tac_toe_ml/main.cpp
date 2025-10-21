#include "TicTacToe.h"
#include "QLearningAgent.h"
#include <iostream>
#include <chrono>

void playAgainstAI(QLearningAgent& ai) {
    TicTacToe game;
    Player humanPlayer = Player::X;
    Player aiPlayer = Player::O;
    
    std::cout << "\n=== HUMAN vs AI ===\n";
    std::cout << "You are X, AI is O\n";
    std::cout << "Enter moves as 'row col' (0-2 for both)\n\n";
    
    while (!game.isGameOver()) {
        game.displayBoard();
        
        if (game.getCurrentPlayer() == humanPlayer) {
            // Human turn
            int row, col;
            std::cout << "Your move (row col): ";
            std::cin >> row >> col;
            
            if (!game.makeMove(row, col, humanPlayer)) {
                std::cout << "Invalid move! Try again.\n";
                continue;
            }
        } else {
            // AI turn
            std::cout << "AI is thinking...\n";
            auto aiMove = ai.getBestAction(game);
            
            if (aiMove.first != -1) {
                game.makeMove(aiMove.first, aiMove.second, aiPlayer);
                std::cout << "AI played: " << aiMove.first << " " << aiMove.second << "\n";
            }
        }
    }
    
    game.displayBoard();
    
    Player winner = game.checkWinner();
    if (winner == humanPlayer) {
        std::cout << "🎉 You won! Great job!\n";
    } else if (winner == aiPlayer) {
        std::cout << "🤖 AI wins! Better luck next time!\n";
    } else {
        std::cout << "🤝 It's a draw! Good game!\n";
    }
}

void aiVsAi(QLearningAgent& ai1, QLearningAgent& ai2, int games = 100) {
    std::cout << "\n=== AI vs AI ===\n";
    std::cout << "Running " << games << " games between two AIs...\n";
    
    int ai1Wins = 0, ai2Wins = 0, draws = 0;
    
    for (int i = 0; i < games; i++) {
        TicTacToe game;
        
        while (!game.isGameOver()) {
            QLearningAgent* currentAI = (game.getCurrentPlayer() == Player::X) ? &ai1 : &ai2;
            Player currentPlayer = game.getCurrentPlayer();
            
            auto move = currentAI->getBestAction(game);
            if (move.first != -1) {
                game.makeMove(move.first, move.second, currentPlayer);
            }
        }
        
        Player winner = game.checkWinner();
        if (winner == Player::X) ai1Wins++;
        else if (winner == Player::O) ai2Wins++;
        else draws++;
    }
    
    std::cout << "Results after " << games << " games:\n";
    std::cout << "AI 1 (X) wins: " << ai1Wins << " (" << (ai1Wins * 100.0 / games) << "%)\n";
    std::cout << "AI 2 (O) wins: " << ai2Wins << " (" << (ai2Wins * 100.0 / games) << "%)\n";
    std::cout << "Draws: " << draws << " (" << (draws * 100.0 / games) << "%)\n";
}

int main() {
    std::cout << "🎮 Tic-Tac-Toe Machine Learning with Q-Learning 🤖\n";
    std::cout << "==================================================\n\n";
    
    // Create AI agents
    QLearningAgent aiX(Player::X);
    QLearningAgent aiO(Player::O);
    
    int choice;
    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Train AI (10,000 episodes)\n";
        std::cout << "2. Train AI (50,000 episodes - intensive)\n";
        std::cout << "3. Play against AI\n";
        std::cout << "4. Watch AI vs AI (100 games)\n";
        std::cout << "5. Save AI brain\n";
        std::cout << "6. Load AI brain\n";
        std::cout << "7. Quick demo (1000 episodes + play)\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                aiX.train(10000);
                aiO.train(10000);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
                std::cout << "Training completed in " << duration.count() << " seconds!\n";
                break;
            }
            
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                aiX.train(50000);
                aiO.train(50000);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
                std::cout << "Intensive training completed in " << duration.count() << " seconds!\n";
                break;
            }
            
            case 3:
                if (aiO.getEpsilon() > 0.5) {
                    std::cout << "⚠️  AI hasn't been trained much yet. Train first for better gameplay!\n";
                }
                playAgainstAI(aiO);
                break;
                
            case 4:
                if (aiX.getEpsilon() > 0.5 || aiO.getEpsilon() > 0.5) {
                    std::cout << "⚠️  AIs haven't been trained much yet. Results may be random!\n";
                }
                aiVsAi(aiX, aiO, 100);
                break;
                
            case 5:
                aiX.saveQTable("ai_x_brain.txt");
                aiO.saveQTable("ai_o_brain.txt");
                break;
                
            case 6:
                aiX.loadQTable("ai_x_brain.txt");
                aiO.loadQTable("ai_o_brain.txt");
                aiX.setEpsilon(0.01); // Set to exploitation mode
                aiO.setEpsilon(0.01);
                break;
                
            case 7: {
                std::cout << "🚀 Quick demo starting...\n";
                auto start = std::chrono::high_resolution_clock::now();
                aiX.train(1000);
                aiO.train(1000);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                std::cout << "Quick training completed in " << duration.count() << " ms!\n";
                
                aiVsAi(aiX, aiO, 10);
                
                char playChoice;
                std::cout << "Want to play against the AI? (y/n): ";
                std::cin >> playChoice;
                if (playChoice == 'y' || playChoice == 'Y') {
                    playAgainstAI(aiO);
                }
                break;
            }
            
            case 0:
                std::cout << "Thanks for playing! 👋\n";
                return 0;
                
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
