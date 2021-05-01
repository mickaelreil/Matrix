#ifndef MATRIX_H_
#define MATRIX_H_
#include <cmath>
#include <iostream>
#include <random>
#include <array>
#include <memory>

using namespace std;

class Matrix {
    public:
        unique_ptr<int[]> matrix;
        int rows;
        int columns;
        static int rand_min;
        static int rand_max;
        static int instances;
        Matrix();
        Matrix( int rows, int columns);
        Matrix(const Matrix& a);
        static int sum(Matrix a);
        int get(int row, int column) const;
        void set(int row, int column, int value) const;
        virtual ~Matrix();
        friend ostream& operator<<(ostream& out, Matrix m);
        static Matrix sum(Matrix a, int axis);
        void operator=(const Matrix& a);
        static Matrix exp(Matrix a);
        friend void operator+=( Matrix a,  int b);
        friend void operator*=( Matrix a,  int b);
        friend void operator/=( Matrix a,  int b);
        friend void operator+=(Matrix a,  Matrix b);
        friend void operator*=(Matrix a, Matrix b);
        friend void operator/=( Matrix a,  Matrix b);
        friend Matrix operator+( Matrix a,  int b);
        friend Matrix operator+( int b,  Matrix a);
        friend Matrix operator-(Matrix a,  int b);
        friend Matrix operator-( int b, Matrix a);
        friend Matrix operator-(Matrix a, Matrix b);
        friend Matrix operator*( Matrix a,  int b);
        friend Matrix operator*( int b, Matrix a);
        friend Matrix operator/( Matrix a,  int b);
        friend Matrix operator/(int b, Matrix a);
        friend Matrix operator+( Matrix a,  Matrix b);
        friend Matrix operator/(Matrix a, Matrix b);
        friend Matrix operator*(Matrix a, Matrix b);
        friend bool operator==( Matrix a,  Matrix b);
        friend bool operator!=( Matrix a,  Matrix b);
        Matrix operator[](unsigned  int index);
        static int rand( double min,  double max);
        static int randint( int min,  int max);
        static Matrix random(int min, int max,  int rows, int columns);
        static Matrix random( int rows,  int columns);
        static Matrix randomint( int rows,  int columns);
        static Matrix randomint( int min,  int max,  int rows, int columns);
        static Matrix zeros(int rows, int columns);
        static Matrix range(int min, int max,  int rows,  int columns);
        static void printException(int exception);
        static Matrix pow(Matrix a, int b);
        static Matrix abs(Matrix a);
        static unsigned int factorial( unsigned int a);
        static Matrix factorial(Matrix a);
        Matrix repeat( unsigned int a);
        Matrix T();
        static Matrix dot(Matrix& a, Matrix& b);
        static int min(Matrix a);
        static Matrix argmin(Matrix a);
    
};

#endif