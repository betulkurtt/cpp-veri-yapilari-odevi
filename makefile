CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -pedantic
SRC = src/main.cpp src/Stack.cpp src/AVLTree.cpp src/Forest.cpp
OBJ = lib/main.o lib/Stack.o lib/AVLTree.o lib/Forest.o
TARGET = bin/Odev2.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

lib/main.o: src/main.cpp include/Forest.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o lib/main.o

lib/Stack.o: src/Stack.cpp include/Stack.h
	$(CXX) $(CXXFLAGS) -c src/Stack.cpp -o lib/Stack.o

lib/AVLTree.o: src/AVLTree.cpp include/AVLTree.h include/Stack.h
	$(CXX) $(CXXFLAGS) -c src/AVLTree.cpp -o lib/AVLTree.o

lib/Forest.o: src/Forest.cpp include/Forest.h include/AVLTree.h include/Stack.h
	$(CXX) $(CXXFLAGS) -c src/Forest.cpp -o lib/Forest.o

clean:
	del /Q lib\*.o bin\*.exe 2>NUL
