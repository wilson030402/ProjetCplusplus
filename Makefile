CXX := g++

# Source files
SRC := main.cpp

# Output executable
OUT := game

# Compiler flags
CXXFLAGS := -std=c++11

# SFML libraries
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Clean rule
clean:
	rm -f $(OUT)

