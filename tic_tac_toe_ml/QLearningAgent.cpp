#include "QLearningAgent.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

QLearningAgent::QLearningAgent(Player symbol, double lr, double df, double eps)
    : playerSymbol(symbol), learningRate(lr), discountFactor(df), 
      epsilon(eps), epsilonDecay(0.995), minEpsilon(0.01),
      rng(std::random_device{}()), dist(0.0, 1.0) {}

int QLearningAgent::getActionIndex(int row, int col) const {
    return row * 3 + col;
}

std::pair<int, int> QLearningAgent::getActionFromIndex(int index) const {
    return {index / 3, index % 3};
}

std::vector<double>& QLearningAgent::getQValues(int state) {
    if (qTable.find(state) == qTable.end()) {
        qTable[state] = std::vector<double>(9, 0.0); // 9 possible actions
    }
    return qTable[state];
}

std::pair<int, int> QLearningAgent::chooseAction(const TicTacToe& game) {
    auto availableMoves = game.getAvailableMoves();
    
    if (availableMoves.empty()) {
        return {-1, -1}; // No valid moves
    }
    
    // Epsilon-greedy strategy
    if (dist(rng) < epsilon) {
        // Random action (exploration)
        std::uniform_int_distribution<int> moveDist(0, availableMoves.size() - 1);
        return availableMoves[moveDist(rng)];
    } else {
        // Best action (exploitation)
        return getBestAction(game);
    }
}

std::pair<int, int> QLearningAgent::getBestAction(const TicTacToe& game) {
    auto availableMoves = game.getAvailableMoves();
    
    if (availableMoves.empty()) {
        return {-1, -1};
    }
    
    int currentState = game.getBoardStateHash();
    auto& qValues = getQValues(currentState);
    
    double bestValue = -std::numeric_limits<double>::infinity();
    std::vector<std::pair<int, int>> bestMoves;
    
    for (const auto& move : availableMoves) {
        int actionIndex = getActionIndex(move.first, move.second);
        if (qValues[actionIndex] > bestValue) {
            bestValue = qValues[actionIndex];
            bestMoves.clear();
            bestMoves.push_back(move);
        } else if (qValues[actionIndex] == bestValue) {
            bestMoves.push_back(move);
        }
    }
    
    // If multiple best moves, choose randomly among them
    std::uniform_int_distribution<int> bestDist(0, bestMoves.size() - 1);
    return bestMoves[bestDist(rng)];
}

void QLearningAgent::updateQValue(int state, int action, double reward, int nextState) {
    auto& currentQValues = getQValues(state);
    auto& nextQValues = getQValues(nextState);
    
    double maxNextQ = *std::max_element(nextQValues.begin(), nextQValues.end());
    double currentQ = currentQValues[action];
    
    // Q-learning update rule
    currentQValues[action] = currentQ + learningRate * (reward + discountFactor * maxNextQ - currentQ);
}

void QLearningAgent::train(int episodes) {
    std::cout << "Training AI for " << episodes << " episodes...\n";
    
    int wins = 0, losses = 0, draws = 0;
    
    for (int episode = 0; episode < episodes; episode++) {
        TicTacToe game;
        std::vector<std::tuple<int, int, int>> history; // state, action, nextState
        
        while (!game.isGameOver()) {
            int currentState = game.getBoardStateHash();
            
            if (game.getCurrentPlayer() == playerSymbol) {
                // AI's turn
                auto action = chooseAction(game);
                if (action.first == -1) break; // No valid moves
                
                int actionIndex = getActionIndex(action.first, action.second);
                game.makeMove(action.first, action.second, playerSymbol);
                
                int nextState = game.getBoardStateHash();
                history.push_back({currentState, actionIndex, nextState});
            } else {
                // Opponent's turn (random player for training)
                auto availableMoves = game.getAvailableMoves();
                if (!availableMoves.empty()) {
                    std::uniform_int_distribution<int> moveDist(0, availableMoves.size() - 1);
                    auto randomMove = availableMoves[moveDist(rng)];
                    Player opponent = (playerSymbol == Player::X) ? Player::O : Player::X;
                    game.makeMove(randomMove.first, randomMove.second, opponent);
                }
            }
        }
        
        // Update Q-values based on game result
        double finalReward = game.getReward(playerSymbol);
        
        // Count results for statistics
        if (finalReward > 0.9) wins++;
        else if (finalReward < -0.9) losses++;
        else draws++;
        
        // Backward pass through history
        for (auto it = history.rbegin(); it != history.rend(); ++it) {
            int state = std::get<0>(*it);
            int action = std::get<1>(*it);
            int nextState = std::get<2>(*it);
            
            updateQValue(state, action, finalReward, nextState);
            finalReward *= 0.9; // Decay reward for earlier moves
        }
        
        // Decay epsilon
        if (episode % 100 == 0) {
            decayEpsilon();
            if (episode % 1000 == 0) {
                std::cout << "Episode " << episode << " - Wins: " << wins 
                         << ", Losses: " << losses << ", Draws: " << draws 
                         << ", Epsilon: " << epsilon << std::endl;
                wins = losses = draws = 0;
            }
        }
    }
    
    std::cout << "Training completed! Q-table size: " << qTable.size() << std::endl;
}

void QLearningAgent::decayEpsilon() {
    epsilon = std::max(minEpsilon, epsilon * epsilonDecay);
}

void QLearningAgent::saveQTable(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : qTable) {
            file << entry.first;
            for (double value : entry.second) {
                file << " " << value;
            }
            file << "\n";
        }
        file.close();
        std::cout << "Q-table saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for saving Q-table" << std::endl;
    }
}

void QLearningAgent::loadQTable(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        qTable.clear();
        
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int state;
            iss >> state;
            
            std::vector<double> values(9);
            for (int i = 0; i < 9; i++) {
                iss >> values[i];
            }
            qTable[state] = values;
        }
        file.close();
        std::cout << "Q-table loaded from " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for loading Q-table" << std::endl;
    }
}
