#pragma once
#include "TicTacToe.h"
#include <unordered_map>
#include <random>
#include <memory>

class QLearningAgent {
private:
    std::unordered_map<int, std::vector<double>> qTable;
    double learningRate;
    double discountFactor;
    double epsilon;
    double epsilonDecay;
    double minEpsilon;
    Player playerSymbol;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    
    // Helper functions
    int getActionIndex(int row, int col) const;
    std::pair<int, int> getActionFromIndex(int index) const;
    std::vector<double>& getQValues(int state);
    
public:
    QLearningAgent(Player symbol, double lr = 0.1, double df = 0.9, double eps = 1.0);
    
    // Main Q-learning functions
    std::pair<int, int> chooseAction(const TicTacToe& game);
    void updateQValue(int state, int action, double reward, int nextState);
    void train(int episodes = 10000);
    
    // Utility functions
    void saveQTable(const std::string& filename) const;
    void loadQTable(const std::string& filename);
    void decayEpsilon();
    double getEpsilon() const { return epsilon; }
    void setEpsilon(double eps) { epsilon = eps; }
    
    // Get best action (for playing after training)
    std::pair<int, int> getBestAction(const TicTacToe& game);
};
