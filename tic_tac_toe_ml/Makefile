CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = tic_tac_toe_ml
SOURCES = main.cpp TicTacToe.cpp QLearningAgent.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET) *.txt

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove build files"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug symbols"
	@echo "  help    - Show this help message"

.PHONY: all clean run debug help
