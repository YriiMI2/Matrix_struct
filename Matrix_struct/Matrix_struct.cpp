
#include <iostream>

using namespace std;

struct Matrix
{
	int** matrix;
	int cols;
	int rows;

	Matrix(int r = 1, int c = 1) {
		rows = r;
		cols = c;
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
		}
	}

	Matrix(int r, int c, int num)
	{
		rows = r;
		cols = c;
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				matrix[i][j] = num;
			}
		}
	}

	Matrix(const Matrix& other) {
		this->cols = other.cols;
		this->rows = other.rows;

		this->matrix = new int* [this->rows];

		for (int i = 0; i < other.rows; i++) {
			this->matrix[i] = new int[this->cols];
			for (int j = 0; j < other.cols; j++)
			{
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}


	Matrix& operator=(const Matrix& other) {

		if (this == &other) return *this;

		for (int i = 0; i < this->rows; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

		this->cols = other.cols;
		this->rows = other.rows;

		this->matrix = new int* [rows];

		for (int i = 0; i < rows; i++) {
			this->matrix[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				(*this)[i][j] = other[i][j];
			}
		}
		return *this;
	}

	~Matrix() {
		for (int i = 0; i < rows; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	int*& operator[](const int n) {
		return matrix[n];
	}

	int* operator[](const int n) const{
		return matrix[n];
	}

	Matrix operator+(const Matrix& other) {
		if (this->cols != other.cols || this->rows != other.rows) {
			return *new Matrix(this->rows, this->cols, 0);
		}
		Matrix result(this->rows, this->cols);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator-(const Matrix& other) {
		if (this->cols != other.cols || this->rows != other.rows) {
			return *new Matrix(this->rows, this->cols, 0);
		}
		Matrix result(this->rows, this->cols);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result[i][j] = this->matrix[i][j] - other[i][j];
			}
		}
		return result;
	}

	Matrix operator*(const Matrix& other) {
		if (this->cols != other.rows) {
			return *new Matrix(this->rows, this->cols, 0);
		}
		Matrix result(this->rows, other.cols);
		for (int i = 0; i < this->rows; i++)
		{
			for (int c = 0; c < other.cols; c++) {
				int sum = 0;
				for (int j = 0; j < this->cols; j++) {
					sum += this->matrix[i][j] * other[j][c];
				}
				result[i][c] = sum;
			}
		}
		return result;
	}
	
};

ostream& operator<<(ostream& output, const Matrix& matrix) {
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			output << matrix.matrix[i][j];
		}
		output << endl;
	}
	return output;
}

istream& operator>>(istream& input, Matrix& matrix) {
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++) {
			input >> matrix[i][j];
		}
	}
	return input;
}


int main()
{

	Matrix m1(3, 4, 1);
	Matrix m2(4, 3, 2);

	cout << m1 << endl << m2 << endl;

	cout << "\nm1+m2:\n" << m1 + m2 << endl;
	cout << "\nm1-m2:\n" << m1 - m2 << endl;
	cout << "\nm1*m2:\n" << m1 * m2 << endl;


}
