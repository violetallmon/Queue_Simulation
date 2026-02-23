.PHONY: all run clean

ifeq ($(OS),Windows_NT)
EXEEXT := .exe
RM_CMD := rm -f
else
EXEEXT :=
RM_CMD := rm -f
endif

CXX := g++
CXXFLAGS := -std=c++11 -Wall -O0 -fno-lto

SRCS := FIFOQueue.cpp PriorityQueue.cpp MathSim.cpp main.cpp Customer.hpp
OBJS := $(filter %.o,$(SRCS:.cpp=.o))
TARGET := mathsim$(EXEEXT)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Building $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Running $(TARGET)..."
ifeq ($(OS),Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
	$(RM_CMD) $(OBJS) $(TARGET)
