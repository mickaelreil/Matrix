#include "Matrix.h"

int Matrix::rand_max = 1;
int Matrix::rand_min = 0;
int Matrix::instances = 0;

Matrix::Matrix() : Matrix(0,0){}

Matrix::Matrix(int rows, int columns){
	this->rows = rows;
	this->columns = columns;
	this->matrix = unique_ptr<int[]>(new int[rows*columns]);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			this->set(i,j,0);
		}
	}
	this->instances++;
}

Matrix::Matrix(const Matrix& a){
	this->rows = a.rows;
	this->columns = a.columns;
	this->matrix = unique_ptr<int[]>(new int[rows*columns]);
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			this->set(i,j,a.get(i,j));
		}
	}
	this->instances++;
}

void Matrix::operator=(const Matrix& a){
	this->matrix.reset();
	this->rows = a.rows;
	this->columns = a.columns;
	this->matrix = unique_ptr<int[]>(new int[rows*columns]);
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			this->set(i,j,a.get(i,j));
		}
	}
}

Matrix::~Matrix(){
	this->instances--;
}



int Matrix::get(int row, int column) const{
	return this->matrix[column + row * this->columns];
}

void Matrix::set(int row, int column, int value) const{
	this->matrix[column + row * this->columns] = value;
}


ostream& operator<<(ostream& out, Matrix m){
	for(int i = 0; i < m.rows; i++){
		out << "[ ";
		for(int j = 0; j < m.columns; j++){
			if(j+1 < m.columns){
				out << m.get(i,j) << ", ";
			}
			else {
				out << m.get(i,j) << " ]" << endl;
			}
		}
	}
	return out;
	
}


int Matrix::sum(Matrix a){
	int sum = 0;
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			sum += a.get(i,j);
		}
	}
	return sum;
}

Matrix Matrix::sum(Matrix a, int axis){
	unique_ptr<Matrix> result;
	switch (axis)
	{
		case 0:
			result = unique_ptr<Matrix>(new Matrix(1, a.columns));
			for(int i = 0; i < a.columns; i++){
				for(int j = 0; j < a.rows; j++){
					result->set(0,i,a.get(j,i)+result->get(0,i));
				}
			}
			break;
		case 1:
			result = unique_ptr<Matrix>(new Matrix(1, a.rows));
			for(int i = 0; i < a.rows; i++){
				for(int j = 0; j < a.columns; j++){
					result->set(0,i,a.get(i,j)+result->get(0,i));	
				}
			}
			break;
	}
	return *result;
}


void Matrix::printException(int exception){
	switch(exception){
		case 0:
			cout << "rows and columns doesn't match" << endl;
			break;
		case 1:
			cout << "division by zero" << endl;
			break;
	}
}

bool operator==( Matrix a,  Matrix b){
	if(a.rows != b.rows || a.columns != b.columns)
		return false;
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			if(a.get(i,j) != b.get(i,j)) return false;
		}
	}
	return true;
}

bool operator!=( Matrix a,  Matrix b){
	if(a.rows != b.rows || a.columns != b.columns)
		return true;
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			if(a.get(i,j) != b.get(i,j)) return true;
		}
	}
	return false;
}

void operator/=( Matrix a,  int b){
	try
	{
		if(b == 0) throw 1;
		a = a / b;
	}
	catch(int exception)
	{
		Matrix::printException(exception);
	}
}

void operator*=( Matrix a,  int b){
	a = a * b;
}

void operator+=( Matrix a,  int b){
	a = a + b;
}

void operator+=(Matrix a,  Matrix b){
	a = a + b;
}

void operator*=(Matrix a, Matrix b){
	a = a * b;
}

void operator/=( Matrix a,  Matrix b){
	try{
		if(a.columns == b.columns && a.rows == b.rows){
			a = a / b;
		}
		else {
			throw 1;
		}
	} catch(int e){
		Matrix::printException(e);
	}
}


Matrix operator/( Matrix a,  int b){
	try
	{
		if(b == 0){
			throw 0;
		}
		else{
			unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
			for(int i = 0; i < a.rows; i++){
				for(int j = 0; j < a.columns; j++){
					if(b==0) throw 0;
					result->set(i,j,b/a.get(i,j));
				}
			}
			return *result;
		}
	}
	catch(int exception)
	{
		Matrix::printException(exception);
	}
}

Matrix operator/(int b, Matrix a){
	try
	{
		unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
		for(int i = 0; i < a.rows; i++){
			for(int j = 0; j < a.columns; j++){
				int q = a.get(i,j);
				if(q==0) throw 0;
				result->set(i,j,b/q);
			}
		}
		return *result;
	}
	catch(int exception)
	{
		Matrix::printException(exception);
	}
}

Matrix operator*(Matrix a,  int b){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,a.get(i,j)*b);
		}
	}
	return *result;
}

Matrix operator*( int b, Matrix a){
	return a * b;
}


Matrix operator-(Matrix a,  int b){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,a.get(i,j)-b);
		}
	}
	return *result;
}

Matrix operator-( int b, Matrix a){
	return (-1 * a) + b;
}

Matrix operator-(Matrix a, Matrix b){
	try {
		if(a.columns == b.columns && a.rows == b.rows){
			unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
			for(int i = 0; i < a.rows; i++){
				for(int j = 0; j < a.columns; j++){
					result->set(i,j,a.get(i,j) - b.get(i,j));
				}
			}
			return *result;
		}
		else {
			throw 0;
		}
	}
	catch(int e){
		Matrix::printException(e);
	}
}

Matrix operator+( Matrix a,  int b){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,a.get(i,j)+b);
		}
	}
	return *result;
}

Matrix operator+( int b,  Matrix a){
	return a + b;
}

Matrix operator+( Matrix a,  Matrix b){
	try {
		if(a.columns == b.columns && a.rows == b.rows){
			unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
			for(int i = 0; i < a.rows; i++){
				for(int j = 0; j < a.columns; j++){
					result->set(i,j,a.get(i,j)+b.get(i,j));
				}
			}
			return *result;
		}
		else {
			throw 0;
		}
	}
	catch(int e){
		Matrix::printException(e);
	}
}

Matrix operator/(Matrix a, Matrix b){
	return a * (1 / b);
}

Matrix Matrix::T(){
	unique_ptr<Matrix> result(new Matrix(this->columns,this->rows));
	for(int i = 0; i < this->columns; i++){
		for(int j = 0; j < this->rows; j++){
			result->set(i,j,this->get(j,i));
		}
	}
	return *result;
}

Matrix Matrix::dot(Matrix& a, Matrix& b){
	try {
		if(a.columns == b.rows){
			unique_ptr<Matrix> result(new Matrix(a.rows,b.columns));
			for(int h = 0; h < a.rows; h++){
				for(int k = 0; k < b.columns; k++){
					for(int i = 0; i < a.columns ; i++){
						for(int j = 0; j < b.rows; j++){
							result->set(h,k,a.get(h,j) * b.get(j,i) + result->get(h,k));
						}
					}
				}
			}
			return *result;
		}
		else {
			throw 0;
	
		}
	}
	catch(int e){
		Matrix::printException(e);
	}
}

Matrix operator*(Matrix a, Matrix b){
	try {
		if(a.columns == b.columns && a.rows == b.rows){
			unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
			for(int i = 0; i < a.rows; i++){
				for(int j = 0; j < a.columns; j++){
					result->set(i,j,a.get(i,j)*b.get(i,j));
				}
			}
			return *result;
			
		}
		else {
			throw 0;
		}
	}
	catch(int e){
		Matrix::printException(e);
	}
}

Matrix Matrix::operator[](unsigned  int index){
	unique_ptr<Matrix> result(new Matrix(1,this->columns));
	for(int j = 0; j < this->columns; j++){
		result->set(0,j,this->get(index,j));
	}
	return *result;
}

int Matrix::min(Matrix a){
	int min = a.get(0,0);
	int current = 0;
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			current = a.get(i,j);
			if(min > current) min = current;
		}
	}
	return min;
}

Matrix Matrix::argmin(Matrix a){
	int min = a.get(0,0);
	int current = 0;
	unique_ptr<Matrix> result(new Matrix(1,2));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			current = a.get(i,j);
			if(min > current){ 
				min = current;
				result->set(0,0,i);
				result->set(0,1,j);  
			}
		}
	}
	return *result;
}
int Matrix::rand( double min,  double max){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> uniform_dist(min, max);
	return uniform_dist(gen);
}

int Matrix::randint( int min,  int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> uniform_dist(min, max);
	return ((int)uniform_dist(gen));
}

Matrix Matrix::random(int min, int max,  int rows,  int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			result->set(i,j,rand(min,max));
		}
	}
	return *result;
}

Matrix Matrix::random( int rows,  int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			result->set(i,j,rand(rand_min,rand_max));
		}
	}
	return *result;
}

Matrix Matrix::randomint( int min,  int max,  int rows, int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			result->set(i,j,randint(min,max));
		}
	}
	return *result;
}

Matrix Matrix::randomint( int rows,  int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			result->set(i,j,randint(rand_min,rand_max));
		}
	}
	return *result;
}

Matrix Matrix::range(int min, int max,  int rows,  int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	int a = (max-min) / (columns-1);
	int b = 0;
	for(int i = 0; i < rows; i++){
		b = min;
		for(int j = 0; j < columns; j++){
			result->set(i,j,b);
			b += a;
		}
	}
	return *result;
}

Matrix Matrix::zeros(int rows, int columns){
	unique_ptr<Matrix> result(new Matrix(rows,columns));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			result->set(i,j,0);
		}
	}
	return *result;
}

Matrix Matrix::pow(Matrix a, int b){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,std::pow(a.get(i,j),b));
		}
	}
	return *result;
}

Matrix Matrix::abs(Matrix a){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,std::abs(a.get(i,j)));
		}
	}
	return *result;
}

unsigned int Matrix::factorial( unsigned int a){
	if(a == 0)
		return 1;
	else
		return a * factorial(a-1);
}

Matrix Matrix::factorial(Matrix a){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,Matrix::factorial(a.get(i,j)));
		}
	}
	return *result;
}

Matrix Matrix::exp(Matrix a){
	unique_ptr<Matrix> result(new Matrix(a.rows,a.columns));
	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			result->set(i,j,std::exp(a.get(i,j)));
		}
	}
	return *result;
}

Matrix Matrix::repeat( unsigned int a){
	unique_ptr<Matrix> result(new Matrix(this->rows*a,this->columns));
	for(int h = 0; h < a; h++){
		for(int i = 0; i < this->rows; i++){
			for(int j = 0; j < this->columns; j++){
				result->set(i+h,j,this->get(i,j));
			}
		}
	}
	return *result;
}