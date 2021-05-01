program: Matrix.h Matrix.cpp main.cpp
	g++ -o program main.cpp Matrix.cpp -std=c++1z
clean:
	rm program
