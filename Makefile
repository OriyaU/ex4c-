
CXX = g++
CXXFLAGS = -std=c++17 -Wall
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = makeTree
TEST_TARGET = tests

SRCS = Main.cpp
HDRS = Node.hpp Tree.hpp
OBJS = $(SRCS:.cpp=.o)

# Compile and link your main program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Compile rule for objects
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove binaries and object files
clean:
	rm -f $(TARGET) $(OBJS) $(TEST_TARGET) test.o

# Rule to compile and run tests
$(TEST_TARGET): $(OBJS) test.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test.o $(SFML_LIBS)
	./$(TEST_TARGET)

# Compile rule for test object
test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# PHONY target to ensure 'tests' is always considered as a target, not a file
.PHONY: clean $(TEST_TARGET)
