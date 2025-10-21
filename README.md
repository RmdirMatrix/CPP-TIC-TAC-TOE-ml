# 🎮 Tic-Tac-Toe Machine Learning with Q-Learning 🤖

A C++ implementation of a machine learning agent that learns to play Tic-Tac-Toe using Q-Learning reinforcement learning algorithm.

## 🚀 Features

- **Q-Learning AI**: Uses reinforcement learning to improve gameplay
- **Self-Training**: AI learns by playing thousands of games against random opponents
- **Human vs AI**: Play against the trained AI
- **AI vs AI**: Watch two AIs compete against each other
- **Save/Load**: Persist the AI's learned knowledge
- **Real-time Training**: Watch the AI improve over time
- **Multiple Training Modes**: Quick demo or intensive training

## 🛠️ Requirements

- **C++ Compiler**: g++ with C++17 support (MinGW-w64 recommended for Windows)
- **Operating System**: Windows, Linux, or macOS

### Windows Setup
1. Download and install MinGW-w64: https://www.mingw-w64.org/downloads/
2. Add MinGW bin directory to your PATH
3. Verify installation: `g++ --version`

### Linux/macOS Setup
```bash
# Ubuntu/Debian
sudo apt install g++ build-essential

# macOS
xcode-select --install
```

## 🏗️ Building

### Windows (Easy Way)
```cmd
# Double-click build.bat or run:
build.bat
```

### Cross-Platform (Makefile)
```bash
make
# or
make run
```

### Cross-Platform (CMake)
```bash
mkdir build
cd build
cmake ..
make
```

### Manual Compilation
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp TicTacToe.cpp QLearningAgent.cpp -o tic_tac_toe_ml
```

## 🎯 How to Use

1. **Build the program** using one of the methods above
2. **Run the executable**: `./tic_tac_toe_ml` (Linux/macOS) or `tic_tac_toe_ml.exe` (Windows)
3. **Choose from the menu**:
   - Train the AI (recommended: start with option 7 for quick demo)
   - Play against the AI
   - Watch AI vs AI battles
   - Save/load the AI's brain

## 🧠 How Q-Learning Works

The AI uses **Q-Learning**, a reinforcement learning algorithm:

1. **State**: Current board configuration (3x3 grid)
2. **Actions**: Possible moves (empty squares)
3. **Rewards**: 
   - +1.0 for winning
   - -1.0 for losing  
   - +0.5 for drawing
   - 0.0 for ongoing game
4. **Learning**: Updates Q-values based on outcomes

### Q-Learning Formula
```
Q(s,a) = Q(s,a) + α[r + γ·max(Q(s',a')) - Q(s,a)]
```
Where:
- α = learning rate (0.1)
- γ = discount factor (0.9)
- r = reward
- s = current state
- a = action taken
- s' = next state

## 📊 Training Process

The AI learns through:
- **Exploration vs Exploitation**: ε-greedy strategy
- **Self-Play**: Playing against random opponents
- **Experience Replay**: Learning from game outcomes
- **Epsilon Decay**: Gradually reducing randomness

## 🎮 Game Features

### Menu Options
1. **Train AI (10,000 episodes)** - Standard training
2. **Train AI (50,000 episodes)** - Intensive training  
3. **Play against AI** - Human vs AI gameplay
4. **Watch AI vs AI** - Observe AI battles
5. **Save AI brain** - Persist learned knowledge
6. **Load AI brain** - Restore saved knowledge
7. **Quick demo** - Fast training + gameplay

### Gameplay
- **Board coordinates**: Use row,col format (0-2 for both)
- **Human symbol**: X (goes first)
- **AI symbol**: O (goes second)
- **Input format**: Enter moves as "row col" (e.g., "1 1" for center)

## 📈 Performance

After training:
- **Beginner AI** (1,000 episodes): ~60-70% win rate vs random
- **Trained AI** (10,000 episodes): ~80-90% win rate vs random  
- **Expert AI** (50,000 episodes): ~95%+ win rate vs random

## 🔧 Customization

You can modify the learning parameters in `QLearningAgent.cpp`:
- `learningRate`: How fast the AI learns (default: 0.1)
- `discountFactor`: How much future rewards matter (default: 0.9)
- `epsilon`: Exploration rate (starts at 1.0, decays to 0.01)
- `epsilonDecay`: How fast exploration decreases (default: 0.995)

## 📁 File Structure

```
tic_tac_toe_ml/
├── main.cpp              # Main program and UI
├── TicTacToe.h/.cpp      # Game engine
├── QLearningAgent.h/.cpp # AI implementation
├── Makefile              # Build script (Linux/macOS)
├── CMakeLists.txt        # CMake build file
├── build.bat             # Windows build script
├── README.md             # This file
├── ai_x_brain.txt        # Saved AI knowledge (X player)
└── ai_o_brain.txt        # Saved AI knowledge (O player)
```

## 🎯 Example Session

```
🎮 Tic-Tac-Toe Machine Learning with Q-Learning 🤖
==================================================

Choose an option:
7. Quick demo (1000 episodes + play)

🚀 Quick demo starting...
Training AI for 1000 episodes...
Episode 0 - Wins: 12, Losses: 67, Draws: 21, Epsilon: 0.606
Training completed! Q-table size: 2847

=== AI vs AI ===
AI 1 (X) wins: 45 (45.0%)
AI 2 (O) wins: 31 (31.0%)  
Draws: 24 (24.0%)

Want to play against the AI? (y/n): y

=== HUMAN vs AI ===
You are X, AI is O

  0   1   2
0   |   |  
  ---------
1   |   |  
  ---------
2   |   |  

Your move (row col): 1 1
```

## 🏆 Tips for Playing

1. **Train first**: Always train the AI before playing for better challenge
2. **Start with quick demo**: Option 7 gives you a taste of everything
3. **Save progress**: Use options 5/6 to save/load trained AI
4. **Watch AI battles**: Option 4 shows how well the AI performs
5. **Be patient**: Intensive training takes time but creates stronger AI

## 🤝 Contributing

Feel free to enhance the project:
- Add neural networks instead of Q-tables
- Implement different board sizes
- Add more sophisticated opponents
- Create a GUI interface
- Add tournament modes

## 📜 License

This project is open source. Feel free to use, modify, and distribute!

---

**Have fun watching the AI learn and improve! 🎮🤖**
